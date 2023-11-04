#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

namespace Lomus {

    namespace Toolbox {

        void printVec3(glm::vec3& vector, const char* name);
        void splitStringToComponents(std::string const& str, const char delim,std::vector<std::string>& out); // For spliting string
        void printVector(std::vector<std::string>& vector);

    }
}



