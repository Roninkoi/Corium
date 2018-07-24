//
// Created by Ronin748 on 11.7.2016.
//

#ifndef CORIUM_TEXT_H
#define CORIUM_TEXT_H

#include <string>
#include <render/renderer.h>
#include <quad.h>
#include <render/textRenderer.h>

//TextRenderer tr;
/*
   class Text {
   public:
    std::string s = "";
    std::string sOld = "";
    Sprite sTex; // sprite that contains the rendered text
    GLuint font; // texture that contains the font
    Quad textQuad; // quad that will be sent to the game renderer

    // Render the string to the texture
    void render()
    {
        //sTex.tex.tex = tr.renderToTex(s);
    }

    // Draw the texture
    void draw(Renderer* rndr)
    {
        if (s != sOld) {
            render();
            sOld = s;
        }
        textQuad.sprite = sTex;
        textQuad.draw(rndr);
    }

    Text()
    {
    }
   };*/

#endif //CORIUM_TEXT_H
