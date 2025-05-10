#include <Camera\Camera.hpp>

Camera::Camera(glm::vec3 new_position, float new_fov):v_Psition(new_position),fov(new_fov),m4_Rotation(1.0f)    {

};
Camera::~Camera(){};


void Camera::Update(){
    v_FRONT = glm::vec3(m4_Rotation * glm::vec4(0, 0,-1, 1));
    v_RIGHT = glm::vec3(m4_Rotation * glm::vec4(1, 0, 0, 1));
    v_UP    = glm::vec3(m4_Rotation * glm::vec4(0, 1, 0, 1));
};

void Camera::Rotate(float x,float y,float z){
    m4_Rotation = glm::rotate(m4_Rotation,z,glm::vec3(0,0,1));
    m4_Rotation = glm::rotate(m4_Rotation,y,glm::vec3(0,1,0));
    m4_Rotation = glm::rotate(m4_Rotation,x,glm::vec3(1,0,0));
    
    
    Update();
};


glm::mat4 Camera::get_Projection(int32_t win_Width,int32_t win_Height){
    float aspect = (float)win_Width / (float)win_Height;

    return glm::perspective(fov,aspect,0.1f,100.0f);
};
glm::mat4 Camera::get_View(){
    return glm::lookAt(v_Psition,v_Psition+v_FRONT, v_UP);
};