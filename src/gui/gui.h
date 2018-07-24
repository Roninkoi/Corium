//
// Created by Ronin748 on 22.12.2015.
//

#ifndef CORIUM_GUI_H
#define CORIUM_GUI_H

#include <quad.h>
#include <render/screenRenderer.h>

class GUI {
public:
Quad crosshair;

Quad hurt;

float ticks = 0.0f;

void drawGUI(ScreenRenderer* scrRndr);

void loadGUI();

GUI()
{
}
};

#endif //CORIUM_GUI_H
