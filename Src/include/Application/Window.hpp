#pragma once
#include <cstdint>
#include <string>

class GLFWwindow;

class Window{
public:
    GLFWwindow* ptr_window;

    void initialize(int32_t Width , int32_t Height, std::string Title);
    void terminate();

    bool isShouldClose();
    void SwapBuffers();
    void Viewport(int32_t Width , int32_t Height);


    void setShouldClose(bool new_state);

    ~Window();
    Window();
};

