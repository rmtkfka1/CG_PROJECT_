#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    glm::vec3 vec1(1.0f, 0, 0);
    glm::vec3 vec2(1.0f, 0, 0);

    glm::vec3 result = glm::cross(vec2, vec1);

    std::cout << "Cross product result: " << result.x <<"  " << result.y <<"  " << result.z << std::endl;

    return 0;
}