#pragma once

#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <map>
#include <string_view>

class Mesh{
    public:

    uint32_t VAO,VBO;
    uint32_t vert_size;
    uint32_t number_of_vertices;

    Mesh(std::vector<float>& buffer, std::vector<uint32_t>& attrib_size);
    ~Mesh();


    void draw();
    void use();
    void unuse();


};