#include "ToolBox.h"

void Lomus::Toolbox::splitStringToComponents(std::string const& str, const char delim, std::vector<std::string>& out) // For spliting string
{
    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, delim)) {
        out.push_back(s);
    }
}

void Lomus::Toolbox::printVec3(glm::vec3& vector, const char* name) {
    std::cout << "Vector Print (ID: " << name << ")  X:" << vector.x << " | Y: " << vector.y << " | Z: " << vector.z << "\n";
}

void Lomus::Toolbox::printVector(std::vector<std::string>& vector) {

}