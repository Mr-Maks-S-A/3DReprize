#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>


class Camera{
    public:
    Camera(glm::vec3 new_position, float new_fov);
    ~Camera();
    
    public:
    float fov;
    glm::vec3 v_Psition;
    glm::vec3 v_UP;
    glm::vec3 v_FRONT;
    glm::vec3 v_RIGHT;
    glm::mat4 m4_Rotation;
    
    public:
    glm::mat4 get_Projection(int32_t win_Width, int32_t win_Height);
    glm::mat4 get_View();
    
    void Rotate(float x,float y,float z);
    void Update();
};