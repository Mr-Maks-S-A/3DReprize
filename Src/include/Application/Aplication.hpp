#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <Application/Window.hpp>
#include <Application/Event.hpp>
#include <Render/Shader/Shader.hpp>
#include <Render/Texture/Texture.hpp>


class Application{
    private:
        Application();
    public:
        Window Win;
    public:
        void main_Loop();
    public:
    static Application& get_app();
    ~Application();
};