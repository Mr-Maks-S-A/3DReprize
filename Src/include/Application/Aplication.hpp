#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>


#include <Application/Window.hpp>
#include <Application/Event.hpp>
#include <Render/Shader/Shader.hpp>
#include <Render/Texture/Texture.hpp>
#include <Camera\Camera.hpp>
#include <Mesh/Mesh.hpp>



class Application{
    private:
        Application();
    public:
        Window Win;
        std::unique_ptr<Camera> Cam;
    public:
        void main_Loop();
    public:
    static Application& get_app();
    ~Application();
};