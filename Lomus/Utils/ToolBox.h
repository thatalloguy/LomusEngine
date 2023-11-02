#pragma once
#include <glm/glm.hpp>
#include <iostream>

namespace Lomus {

    namespace Toolbox {

        void printVec3(glm::vec3& vector, const char* name) {
            std::cout << "Vector Print (ID: " << name << ")  X:" << vector.x << " | Y: " << vector.y << " | Z: " << vector.z << "\n";
        }



    }
}



