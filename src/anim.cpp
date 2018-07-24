//
// Created by Ronin748 on 28.7.2017.
//

#include <util/objParser.h>
#include <anim.h>

void Anim::draw(Renderer* renderer)
{
        currentFrame.draw(renderer, &tex);
}

void Anim::render(Renderer* renderer)
{
        currentFrame.objMatrix = phys.getMatrix();
        currentFrame.render(renderer, &tex);
}

void Anim::drawShadows(Renderer* renderer)
{
        currentFrame.drawShadows(renderer);
}

void Anim::renderShadows(Renderer* renderer)
{
        currentFrame.objMatrix = phys.getMatrix();
        currentFrame.renderShadows(renderer);
}

void Anim::tick(float s) {
        if (s >= 0.0f)
                spd = s;

        bool finished = true;

        ticks += spd;

        for (int i = 0;
             i + 2 < frames[thisIndex].rawVertexBufferData.size() && i + 2 < currentFrame.rawVertexBufferData.size() &&
             i + 2 < frames[previousIndex].rawVertexBufferData.size(); i += 4) {
                glm::vec3 frameVertex = glm::vec3(frames[thisIndex].rawVertexBufferData[i],
                                                  frames[thisIndex].rawVertexBufferData[i + 1],
                                                  frames[thisIndex].rawVertexBufferData[i + 2]);
                glm::vec3 previousVertex = glm::vec3(frames[previousIndex].rawVertexBufferData[i],
                                                     frames[previousIndex].rawVertexBufferData[i + 1],
                                                     frames[previousIndex].rawVertexBufferData[i + 2]);
                glm::vec3 thisVertex = glm::vec3(currentFrame.rawVertexBufferData[i],
                                                 currentFrame.rawVertexBufferData[i + 1],
                                                 currentFrame.rawVertexBufferData[i + 2]);

                glm::vec3 nextVertex = glm::vec3(frames[nextIndex].rawVertexBufferData[i],
                                                 frames[nextIndex].rawVertexBufferData[i + 1],
                                                 frames[nextIndex].rawVertexBufferData[i + 2]);

                glm::vec3 midVertex = (nextVertex + frameVertex) / 2.0f;

                if (interpolation > 0) {
                        if (ticks < 1.0f) {
                                switch (interpolation) {
                                case 0:
                                        thisVertex += (frameVertex - thisVertex) * spd;
                                        break;
                                case 1:
                                        thisVertex += ((frameVertex - previousVertex)) * (float) (
                                                sin((glm::length(frameVertex - thisVertex) /
                                                     glm::length(frameVertex - previousVertex)) * M_PI) + 0.005f) * spd;
                                        break;
                                case 2:
                                        thisVertex += (frameVertex - previousVertex) * spd;
                                        break;
                                case 3:
                                        thisVertex += (((frameVertex - previousVertex) * (1.0f - ticks) +
                                                        (nextVertex - frameVertex) * (ticks)) * 0.2f +
                                                       (frameVertex - previousVertex) * 0.8f) * spd;
                                        break;
                                case 4:
                                        thisVertex = frameVertex;
                                        break;
                                default:
                                        thisVertex += (frameVertex - thisVertex) * spd;
                                        break;
                                }

                                finished = false;
                        }
                }
                else {
                        if (glm::length(frameVertex - thisVertex) > spd*0.5f) {
                                thisVertex += (frameVertex - thisVertex) * spd;
                                finished = false;
                        }
                }
                /*else {
                    thisVertex = frameVertex;
                   }*/

                currentFrame.rawVertexBufferData[i] = thisVertex.x;
                currentFrame.rawVertexBufferData[i + 1] = thisVertex.y;
                currentFrame.rawVertexBufferData[i + 2] = thisVertex.z;
        }

        if (finished) {
                //currentFrame = frames[thisFrame]; // copy tex etc.

                ticks = 0.0f;

                if (frameIndex.size() > 1)
                        interpolation = 3;
                else
                        interpolation = 0;

                previousFrame = thisFrame;
                thisFrame += 1;

                if (thisFrame >= frameIndex.size())
                        thisFrame = 0;

                nextFrame = thisFrame;
                nextFrame += 1;
                if (nextFrame >= frameIndex.size())
                        nextFrame = 0;

                thisIndex = frameIndex[thisFrame];
                previousIndex = frameIndex[previousFrame];
                nextIndex = frameIndex[nextFrame];

                currentFrame.texBufferData = frames[thisIndex].texBufferData;
        }

        // tranform current frame
        currentFrame.objMatrix = phys.getMatrix();
        currentFrame.update();
}

// path to keyframe, to load single frame, set numFrames to 0 and path will be absolute
// to set automatic progressive frames, set frameI to {}
// to skip texture loading, set texpath to ""
// multi-frame loading is done by setting path to "path/animname_" (+ index * numFrames)
void Anim::loadAnim(std::string path, std::string texpath, int numFrames, std::vector<int> frameI) {
        if (texpath != "")
                tex.loadTexture(texpath);
        clearFrames();
        for (int i = 0; i < numFrames; ++i) {
                std::string zeroes = "";
                for (int j = 5 - to_string(i).length(); j >= 0; --j)
                        zeroes += "0";
                Mesh newF;
                newF = loadObj(path + to_string(i) + ".obj");

                addFrame(&newF);

                //gamePrint(path + zeroes + to_string(i) + ".obj");
        }
        if (numFrames == 0) {
                Mesh newF = loadObj(path);
                addFrame(&newF);
        }
        if (frameI.size() == 0) {
                frameIndex.resize(frames.size());
                for (int i = 0; i < frames.size(); ++i)
                        frameIndex[i] = i;
        }
        else {
                frameIndex = frameI;
        }

        thisIndex = frameIndex[thisFrame];
        previousIndex = frameIndex[previousFrame];
        nextIndex = frameIndex[nextFrame];
}

void Anim::addFrame(Mesh *new_frame) {
        if (new_frame->vertexBufferData.size() > 0) {
                frames.push_back(*new_frame);

                currentFrame = frames[0];

                thisFrame = 0;
                previousFrame = thisFrame;
                thisFrame += 1;

                if (thisFrame >= frameIndex.size())
                        thisFrame = 0;

                nextFrame = thisFrame;
                nextFrame += 1;
                if (nextFrame >= frameIndex.size())
                        nextFrame = 0;
        }
}

void Anim::resetFrames() {
        ticks = 0.0f;

        thisFrame = 0;
        previousFrame = thisFrame;
        thisFrame += 1;

        if (thisFrame >= frameIndex.size())
                thisFrame = 0;

        nextFrame = thisFrame;
        nextFrame += 1;
        if (nextFrame >= frameIndex.size())
                nextFrame = 0;

        thisIndex = frameIndex[thisFrame];
        previousIndex = frameIndex[previousFrame];
        nextIndex = frameIndex[nextFrame];
}

void Anim::clearFrames() {
        frames.clear();
}

void Anim::setAnim(float new_spd, std::vector<int> fi, bool immediate)
{
        if (finished() || immediate) {
                frameIndex = fi;

                if (new_spd > 0.0f)
                        setSpd(new_spd);

                if (fi.size() > 1)
                        interpolation = 3;
                else
                        interpolation = 0;

                if (thisIndex != fi[0]) {
                        previousIndex = thisIndex;
                        thisIndex = fi[0];
                        if (fi.size() > 1) nextIndex = fi[1];
                        else nextIndex = fi[0];
                }
        }
}

void Anim::setSpd(float new_spd)
{
        spd = new_spd;
}

bool Anim::finished()
{
        bool returns = (ticks == 0.0f && thisFrame == 0);

        return returns;
}

void Anims::draw(Renderer* renderer)
{
        animFrame.draw(renderer, &tex);
}

void Anims::render(Renderer* renderer)
{
        animFrame.render(renderer, &tex);
}

void Anims::drawShadows(Renderer* renderer)
{
        animFrame.drawShadows(renderer);
}

void Anims::renderShadows(Renderer* renderer)
{
        animFrame.renderShadows(renderer);
}

void Anims::loadTemplate(std::string path, std::string texpath)
{
        templateFrame = loadObj(path);
        tex.loadTexture(texpath);
}

void Anims::addAnim(std::string path, int numFrames, float spd, std::vector<int> frameI)
{
        Anim newAnim;
        newAnim.loadAnim(path, "", numFrames, frameI);
        newAnim.setAnim(spd, frameI);

        anims.push_back(newAnim);

        resetStates();
}

void Anims::clearAnims()
{
        std::vector<Anim> swapVec; // try to free memory to system
        anims.swap(swapVec);

        anims.clear();
}

void Anims::resetStates()
{
        anim_running.resize(anims.size());
        for (int i = 0; i < anims.size(); ++i) {
                anim_running[i] = false;
        }

        animFrame = templateFrame;
}

void Anims::tick()
{
        for (int i = 0; i < anims.size(); ++i) {
                anims[i].tick();
        }

        for (int i = 0; i < templateFrame.rawVertexBufferData.size(); ++i) {
                float dv = templateFrame.rawVertexBufferData[i];
                float dt = templateFrame.texBufferData[i];

                for (int j = 0; j < anims.size(); ++j) {
                        if (anim_running[j] || !anims[j].finished()) {
                                dv += anims[j].currentFrame.rawVertexBufferData[i] - templateFrame.rawVertexBufferData[i];
                                dt += anims[j].currentFrame.texBufferData[i] - templateFrame.texBufferData[i];
                        }
                }

                animFrame.rawVertexBufferData[i] = dv;
                animFrame.texBufferData[i] = dt;
        }

        animFrame.objMatrix = phys.getMatrix();
        animFrame.update();
}
