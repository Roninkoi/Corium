//
// Created by Roni A. Koitermaa on 18.12.2015.
//

#ifndef CORIUM_TOSTRING_H
#define CORIUM_TOSTRING_H

#include <string>
#include <sstream>

template<typename T>
std::string to_string(const T &n)
{
        std::ostringstream stm;
        stm << n;
        return stm.str();
}

std::string vec_to_string(glm::vec3 v)
{
        return "(" + to_string(v[0]) + ", " + to_string(v[1]) + ", " + to_string(v[2]) + ")";
}

#endif //CORIUM_TOSTRING_H
