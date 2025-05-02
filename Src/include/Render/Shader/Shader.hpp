#pragma once

#include <cstdint>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/glm.hpp>




class Shader{
    public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    
    public:

    void use();
    
    template<typename T>
    requires std::is_same<T, glm::vec2>::value 
          || std::is_same<T, glm::vec3>::value
          || std::is_same<T, glm::vec4>::value
          || std::is_same<T, glm::mat2>::value
          || std::is_same<T, glm::mat3>::value
          || std::is_same<T, glm::mat4>::value
    void uniform(uint32_t value_id ,T valude_data);

    public:
    uint32_t m_ID;


};