#pragma once

#include <cstdint>
#include <iostream>
#include <type_traits>

#include <glad/glad.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>




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
    || std::is_same<T, glm::mat2x2>::value
    || std::is_same<T, glm::mat3x3>::value
    || std::is_same<T, glm::mat4x4>::value
    void uniform(uint32_t value_id ,T valude_data){
            use();
        
        if constexpr (std::is_same<T, glm::vec2>::value){
                glUniform2f(value_id,valude_data);
            }
        if constexpr (std::is_same<T, glm::vec3>::value){
                glUniform3f(value_id,valude_data);
            }
        if constexpr (std::is_same<T, glm::vec4>::value){
                glUniform4f(value_id,valude_data);
            }
        
        if constexpr (std::is_same<T, glm::mat2x2>::value){
                glUniformMatrix2fv(value_id, 1, GL_FALSE, glm::value_ptr(valude_data));
            }
        if constexpr (std::is_same<T, glm::mat3x3>::value){
                glUniformMatrix3fv(value_id, 1, GL_FALSE, glm::value_ptr(valude_data));
            }
        if constexpr (std::is_same<T, glm::mat4x4>::value){
                glUniformMatrix4fv(value_id, 1, GL_FALSE, glm::value_ptr(valude_data));
            }
        }

    public:
    uint32_t m_ID;


};