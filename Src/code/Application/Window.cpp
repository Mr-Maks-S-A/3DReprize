
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <Application/Window.hpp>


void Window::setShouldClose(bool new_state){
    glfwSetWindowShouldClose(ptr_window, new_state);
};



void Window::initialize(int32_t Width , int32_t Height, std::string Title){
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    ptr_window = glfwCreateWindow(Width, Height, Title.c_str(), NULL, NULL);
    if (!ptr_window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    };

    glfwMakeContextCurrent(ptr_window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    };

};

void Window::terminate(){
    glfwDestroyWindow(ptr_window);
    glfwTerminate();
};

bool Window::isShouldClose(){
    return (bool)glfwWindowShouldClose(ptr_window);
};
void Window::SwapBuffers(){
    glfwSwapBuffers(ptr_window);
}

void Window::Viewport(int32_t Width , int32_t Height){
    glViewport(0,0,Width,Height);
};


Window::Window(){};
Window::~Window(){
    terminate();
};