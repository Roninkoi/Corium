//
// Created by Roni A. Koitermaa on 18.12.2015.
//

#ifndef CORIUM_CRM_H
#define CORIUM_CRM_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
#include <chrono>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <util/toString.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

void gamePrint(std::string s);

void gameRefresh();

void gameScript(std::string s);

#endif //CORIUM_CRM_H
