//
// Created by Roni A. Koitermaa on 18.12.2015.
//

#include "input.h"

void Input::getKeys(GLFWwindow* window)
{
    ++ticks;
    for (int i = 0; i < keyDown.size(); ++i) {
        if (glfwGetKey(window, i)) {
            keyDown[i] = true;
        }
        else {
            keyDown[i] = false;
            //keyPressed[i] = true;
        }

        if (keyDown[i] && ticks%60 == 0)
            printf("key %s%s", &to_string(i)[0], " pressed!\n");
    }

    thisWindow = window;
}

void Input::getMouse(GLFWwindow *window)
{
    mouse_posOld = mouse_pos;
    glfwGetCursorPos(window, &mouse_pos.x, &mouse_pos.y);
    mouse_posDiff = mouse_pos - mouse_posOld;

    for (int i = 0; i < mouseDown.size(); ++i) {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) {

        }
        else {

        }
    }
}

bool Input::getKey(int id)
{
    return glfwGetKey(thisWindow, id);
}
