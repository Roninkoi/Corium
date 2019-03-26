#include <mesh.h>
#include <util/triIsect.h>

std::vector<float> transform_mesh(std::vector<float> data, glm::mat4 matrix)
{
        std::vector<float> newData;
        newData.resize(data.size());
        for (int i = 0; i < newData.size(); i += 4) {
                /* multiply vector with the matrix to pre-calculate vertex data for rendering */
                glm::vec4 v2 =
                        matrix * glm::vec4(data[i], data[i + 1], data[i + 2],
                                           data[i + 3]);

                /* get matrix translation data from the bottom row */
                newData[i] = v2.x + matrix[3][0];
                newData[i + 1] = v2.y + matrix[3][1];
                newData[i + 2] = v2.z + matrix[3][2];
                newData[i + 3] = v2.w + matrix[3][3];
        }
        return newData;
}

glm::vec4 transform_vec(glm::vec4 vec, glm::mat4 matrix)
{
        glm::mat4 imatrix = glm::inverse(matrix);
        glm::vec4 newvec = vec;
        newvec -= glm::vec4(matrix[3][0], matrix[3][1], matrix[3][2], 0.0f);

        return newvec;
}

glm::mat4 mesh_inverse(glm::mat4 matrix)
{
        glm::mat4 newmat = matrix;
        newmat = glm::inverse(newmat);
        return newmat;
}

bool Mesh::intersects(Mesh *another)
{
        bool returns = false;
        collisionNormal = glm::vec3(0.0f);
        another->collisionNormal = glm::vec3(0.0f);

        collisionCenter = glm::vec3(0.0f);
        another->collisionCenter = glm::vec3(0.0f);

        int collision_num = 0;

        for (int j = 0; j < another->indexBufferData.size(); j += 3) {
                float u0[] = {another->vertexBufferData[another->indexBufferData[j] * 4],
                              another->vertexBufferData[another->indexBufferData[j] * 4 + 1],
                              another->vertexBufferData[another->indexBufferData[j] * 4 + 2]};

                bool foundisect = false;
                for (int i = 0; i < indexBufferData.size() && !foundisect; i += 3) {
                        float v0[] = {vertexBufferData[indexBufferData[i] * 4],
                                      vertexBufferData[indexBufferData[i] * 4 + 1],
                                      vertexBufferData[indexBufferData[i] * 4 + 2]};

                        if (glm::length((glm::vec3(v0[0], v0[1], v0[2]) - glm::vec3(u0[0], u0[1], u0[2]))) <
                            (triangle_size+another->triangle_size)) {
                                float u1[] = {another->vertexBufferData[another->indexBufferData[j + 1] * 4],
                                              another->vertexBufferData[another->indexBufferData[j + 1] * 4 + 1],
                                              another->vertexBufferData[another->indexBufferData[j + 1] * 4 + 2]};
                                float u2[] = {another->vertexBufferData[another->indexBufferData[j + 2] * 4],
                                              another->vertexBufferData[another->indexBufferData[j + 2] * 4 + 1],
                                              another->vertexBufferData[another->indexBufferData[j + 2] * 4 + 2]};

                                float v1[] = {vertexBufferData[indexBufferData[i + 1] * 4],
                                              vertexBufferData[indexBufferData[i + 1] * 4 + 1],
                                              vertexBufferData[indexBufferData[i + 1] * 4 + 2]};
                                float v2[] = {vertexBufferData[indexBufferData[i + 2] * 4],
                                              vertexBufferData[indexBufferData[i + 2] * 4 + 1],
                                              vertexBufferData[indexBufferData[i + 2] * 4 + 2]};
                                float vn[] = {another->normalBufferData[j],
                                              another->normalBufferData[j + 1],
                                              another->normalBufferData[j + 2]};
                                float un[] = {normalBufferData[i],
                                              normalBufferData[i + 1],
                                              normalBufferData[i + 2]};

                                int cp = 0;
                                float vi[3] = {0.0f, 0.0f, 0.0f};
                                float ui[3] = {0.0f, 0.0f, 0.0f};
                                if (tri_tri_intersection_test_3d(v0, v1, v2, u0, u1, u2, &cp, vi, ui)) {
                                        glm::vec3 tcn = normalize(glm::vec3(another->normalBufferData[j],
                                                                            another->normalBufferData[j + 1],
                                                                            another->normalBufferData[j + 2])) *(float)another->staticity;
                                        glm::vec3 acn = normalize(glm::vec3(normalBufferData[i],
                                                                            normalBufferData[i + 1],
                                                                            normalBufferData[i + 2])) *(float)staticity;

                                        glm::vec3 pn = fabs(std::max(0.0f, std::max(0.0f, glm::dot(tcn, -acn))))*normalize(tcn-acn);

                                        if (glm::length(pn) <= 0.0f) {
                                                pn = normalize(glm::vec3(0.0f, (tcn.y - acn.y), 0.0f));
                                        }
                                        if (glm::length(pn) <= 0.0f) {
                                                collisionNormal += tcn;
                                                another->collisionNormal += acn;
                                        }

                                        collisionNormal += pn;
                                        another->collisionNormal += -pn;

                                        returns = true;

                                        glm::vec3 cv = glm::vec3(0.0f);
                                        glm::vec3 viv = glm::vec3(vi[0], vi[1], vi[2]);
                                        glm::vec3 uiv = glm::vec3(ui[0], ui[1], ui[2]);

                                        cv += viv;
                                        cv += uiv;
                                        cv /= 2.0f;

                                        glm::vec3 newtcc = glm::vec3(0.0f);

                                        glm::vec3 newacc = glm::vec3(0.0f);

                                        if (glm::length(viv - boundingSphereCenter) < glm::length(uiv - boundingSphereCenter))
                                                newtcc = viv;
                                        else
                                                newtcc = uiv;
                                        if (glm::length(viv - another->boundingSphereCenter) < glm::length(uiv - another->boundingSphereCenter))
                                                newacc = viv;
                                        else
                                                newacc = uiv;

                                        glm::vec3 tcc = newtcc;
                                        glm::vec3 acc = newacc;

                                        collisionCenter += tcc - boundingSphereCenter;
                                        another->collisionCenter += acc - another->boundingSphereCenter;

                                        collision_num += 1;
                                }
                        }
                }
        }

        if (collision_num > 0) {
                collisionCenter /= collision_num;
                another->collisionCenter /= collision_num;

                if (glm::length(collisionCenter) > glm::length(boundingSphereRadius))
                        collisionCenter = normalize(collisionCenter)*glm::length(boundingSphereRadius);
                if (glm::length(another->collisionCenter) > glm::length(another->boundingSphereRadius))
                        another->collisionCenter = normalize(another->collisionCenter)*glm::length(another->boundingSphereRadius);

                collisionNormal = normalize(collisionNormal);
                another->collisionNormal = normalize(another->collisionNormal);
        }

        if (returns) {
                isIntersecting = true;
                another->isIntersecting = true;
        }

        // NULL checks
        if (!nnv(collisionNormal)) {
                collisionNormal = glm::vec3(0.0f);
        }
        if (!nnv(another->collisionNormal)) {
                another->collisionNormal = glm::vec3(0.0f);
        }
        if (!nnv(collisionCenter)) {
                collisionCenter = glm::vec3(0.0f);
        }
        if (!nnv(another->collisionCenter)) {
                another->collisionCenter = glm::vec3(0.0f);
        }

        return returns;
}

bool Mesh::sphereIsect(Mesh *another, glm::vec3 s, float r)
{
        bool returns = false;
        collisionNormal = glm::vec3(0.0f);

        collisionCenter = glm::vec3(0.0f);

        float sa[] = {s.x, s.y, s.z};

        int collision_num = 0;

        bool foundisect = false;
        for (int i = 0; i < indexBufferData.size() && !foundisect; i += 3) {
                float v0[] = {vertexBufferData[indexBufferData[i] * 4],
                              vertexBufferData[indexBufferData[i] * 4 + 1],
                              vertexBufferData[indexBufferData[i] * 4 + 2]};

                if (glm::length((glm::vec3(v0[0], v0[1], v0[2]) - s)) <
                    (triangle_size+r)) {
                        float v1[] = {vertexBufferData[indexBufferData[i + 1] * 4],
                                      vertexBufferData[indexBufferData[i + 1] * 4 + 1],
                                      vertexBufferData[indexBufferData[i + 1] * 4 + 2]};
                        float v2[] = {vertexBufferData[indexBufferData[i + 2] * 4],
                                      vertexBufferData[indexBufferData[i + 2] * 4 + 1],
                                      vertexBufferData[indexBufferData[i + 2] * 4 + 2]};

                        int cp = 0;
                        float vi[3] = {0.0f, 0.0f, 0.0f};
                        if (tri_sphere_intersection_test_3d(v0, v1, v2, sa, r)) {
                                glm::vec3 acn = normalize(glm::vec3(normalBufferData[i],
                                                                    normalBufferData[i + 1],
                                                                    normalBufferData[i + 2]));
                                glm::vec3 tcn = -acn;

                                collisionNormal += tcn;
                                another->collisionNormal += acn;

                                returns = true;

                                collisionCenter += s;
                                another->collisionCenter += s;

                                collision_num += 1;
                        }
                }
        }

        if (collision_num > 0) {
                collisionCenter /= collision_num;
                another->collisionCenter /= collision_num;

                if (glm::length(collisionCenter) > glm::length(boundingSphereRadius))
                        collisionCenter = normalize(collisionCenter)*glm::length(boundingSphereRadius);
                if (glm::length(another->collisionCenter) > glm::length(another->boundingSphereRadius))
                        another->collisionCenter = normalize(another->collisionCenter)*glm::length(another->boundingSphereRadius);

                collisionNormal = normalize(collisionNormal);
                another->collisionNormal = normalize(another->collisionNormal);
        }

        if (returns) {
                isIntersecting = true;
                another->isIntersecting = true;
        }

        // NULL checks
        if (!nnv(collisionNormal)) {
                collisionNormal = glm::vec3(0.0f);
        }
        if (!nnv(another->collisionNormal)) {
                another->collisionNormal = glm::vec3(0.0f);
        }
        if (!nnv(collisionCenter)) {
                collisionCenter = glm::vec3(0.0f);
        }
        if (!nnv(another->collisionCenter)) {
                another->collisionCenter = glm::vec3(0.0f);
        }

        return returns;
}

void Mesh::getNormals()
{
        normalBufferData.resize(indexBufferData.size());

        for (int i = 0; i < indexBufferData.size(); i += 3) {
                float v0[] = {vertexBufferData[indexBufferData[i] * 4],
                              vertexBufferData[indexBufferData[i] * 4 + 1],
                              vertexBufferData[indexBufferData[i] * 4 + 2]};
                float v1[] = {vertexBufferData[indexBufferData[i + 1] * 4],
                              vertexBufferData[indexBufferData[i + 1] * 4 + 1],
                              vertexBufferData[indexBufferData[i + 1] * 4 + 2]};
                float v2[] = {vertexBufferData[indexBufferData[i + 2] * 4],
                              vertexBufferData[indexBufferData[i + 2] * 4 + 1],
                              vertexBufferData[indexBufferData[i + 2] * 4 + 2]};

                glm::vec3 normal = normalize(glm::cross(glm::vec3(v1[0] - v0[0], v1[1] - v0[1], v1[2] - v0[2]),
                                                        glm::vec3(v2[0] - v0[0], v2[1] - v0[1], v2[2] - v0[2])));

                normalBufferData[i] = normal.x;
                normalBufferData[i + 1] = normal.y;
                normalBufferData[i + 2] = normal.z;
        }
        vertexNormalBufferData.clear();
        vertexNormalBufferData.resize(vertexBufferData.size());

        for (int i = 0; i < vertexNormalBufferData.size(); i += 4) {
                for (int j = 0; j < indexBufferData.size(); j += 3) {
                        if (indexBufferData[j] == i / 4 || indexBufferData[j + 1] == i / 4 || indexBufferData[j + 2] == i / 4) {
                                vertexNormalBufferData[i] += normalBufferData[j];
                                vertexNormalBufferData[i + 1] += normalBufferData[j + 1];
                                vertexNormalBufferData[i + 2] += normalBufferData[j + 2];
                                vertexNormalBufferData[i + 3] += 0.0f;
                        }
                }
        }
}

// bounding sphere intersection test
bool Mesh::bsi(Mesh* another)
{
        if (glm::length(boundingSphereCenter-another->boundingSphereCenter) <=
            (boundingSphereRadius + another->boundingSphereRadius))
                return true;
        else
                return false;
}

void Mesh::getBoundingSphere()
{
        glm::vec3 vertSum = glm::vec3(0.0f);
        int vertNum = 0;

        for (int i = 0; i < vertexBufferData.size(); i += 4) {
                vertSum += glm::vec3(vertexBufferData[i], vertexBufferData[i + 1], vertexBufferData[i + 2]);
                ++vertNum;
        }

        vertSum /= vertNum;

        boundingSphereCenter = vertSum;

        float maxRadius = 0.0f;

        for (int i = 0; i < vertexBufferData.size(); i += 4) {
                float dist = glm::length(glm::vec3(vertexBufferData[i], vertexBufferData[i + 1], vertexBufferData[i + 2]) -
                                         boundingSphereCenter);

                if (dist > maxRadius) {
                        maxRadius = dist;
                }
        }

        boundingSphereRadius = maxRadius;
}

void Mesh::update()
{
        vertexBufferData = transform(rawVertexBufferData, objMatrix);
        getNormals();
        getBoundingSphere();
        //triangleSizeCheck();
}

std::vector<float> Mesh::transform(std::vector<float> data, glm::mat4 matrix)
{
        std::vector<float> newData;
        newData.resize(data.size());
        for (int i = 0; i < newData.size(); i += 4) {
                /* multiply vector with the matrix to pre-calculate vertex data for rendering */
                glm::vec4 v2 =
                        matrix * glm::vec4(data[i], data[i + 1], data[i + 2],
                                           data[i + 3]);

                /* get matrix translation data from the bottom row */
                newData[i] = v2.x + matrix[3][0];
                newData[i + 1] = v2.y + matrix[3][1];
                newData[i + 2] = v2.z + matrix[3][2];
                newData[i + 3] = v2.w + matrix[3][3];
        }
        return newData;
}

void Mesh::triangleSizeCheck()
{
        int indices = 0;
        for (int i = 0; i < indexBufferData.size() / 3.0f; i += 1) {
                // check triangle size
                glm::vec3 v1 = glm::vec3(vertexBufferData[indexBufferData[indices] * 4],
                                         vertexBufferData[indexBufferData[indices] * 4 + 1],
                                         vertexBufferData[indexBufferData[indices] * 4 + 2]);
                glm::vec3 v2 = glm::vec3(vertexBufferData[indexBufferData[indices + 1] * 4],
                                         vertexBufferData[indexBufferData[indices + 1] * 4 + 1],
                                         vertexBufferData[indexBufferData[indices + 1] * 4 + 2]);
                glm::vec3 v3 = glm::vec3(vertexBufferData[indexBufferData[indices + 2] * 4],
                                         vertexBufferData[indexBufferData[indices + 2] * 4 + 1],
                                         vertexBufferData[indexBufferData[indices + 2] * 4 + 2]);
                float ts = std::max(glm::length(v1 - v2), std::max(glm::length(v2 - v3), glm::length(v3 - v1)));
                if (ts >= triangle_size) {
                        triangle_size = std::min(ts, MAX_TRIANGLE_SIZE);
                }

                indices += 3;
        }
}

void Mesh::setCol(glm::vec4 newCol)
{
        for (int i = 0; i < colBufferData.size(); i += 4) {
                colBufferData[0 + i] = newCol.r;
                colBufferData[1 + i] = newCol.g;
                colBufferData[2 + i] = newCol.b;
                colBufferData[3 + i] = newCol.a;
        }
}

void Mesh::draw(Renderer* renderer, Texture* tex)
{
        renderer->draw(tex, &vertexBufferData, &vertexNormalBufferData, &texBufferData, &colBufferData, &indexBufferData);
}

void Mesh::render(Renderer* renderer, Texture* tex)
{
        renderer->render(tex, &objMatrix, &rawVertexBufferData, &vertexNormalBufferData, &texBufferData, &colBufferData, &indexBufferData);
}

void Mesh::drawShadows(Renderer* renderer)
{
        renderer->drawShadows(&vertexBufferData, &indexBufferData);
}

void Mesh::renderShadows(Renderer* renderer)
{
        renderer->renderShadows(&objMatrix, &rawVertexBufferData, &indexBufferData);
}
