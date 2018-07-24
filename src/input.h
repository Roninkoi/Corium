//
// Created by Ronin748 on 18.12.2015.
//

#ifndef CORIUM_INPUT_H
#define CORIUM_INPUT_H

#include <crm.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Input {
public:
void getKeys(GLFWwindow *window);
void getMouse(GLFWwindow *window);

std::vector<bool> keyDown;
std::vector<bool> keyPressed;

std::vector<bool> mouseDown;

glm::dvec2 mouse_pos;
glm::dvec2 mouse_posOld;
glm::dvec2 mouse_posDiff;
float mouse_spd;

int jsnum = 0;     // joystick number

bool window_focus;
bool focused;

bool fullscreen = false;

int ticks;

GLFWwindow* thisWindow;

bool getKey(int id);

Input()
{
        window_focus = true;
        focused = false;

        mouse_spd = 1.0;

        keyDown.resize(256);
        keyPressed.resize(256);
        mouseDown.resize(3);

        mouse_pos = glm::vec2(0.0f, 0.0f);

        ticks = 0;

        std::fill(keyDown.begin(), keyDown.end(), false);
        std::fill(keyPressed.begin(), keyPressed.end(), false);
        std::fill(mouseDown.begin(), mouseDown.end(), false);
}
};

#endif //CORIUM_INPUT_H
