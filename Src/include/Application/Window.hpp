#pragma once
#include <cstdint>
#include <string>

class GLFWwindow;

class Window{
public:
    int32_t m_Width , m_Height;
    GLFWwindow* ptr_window;

    void initialize(int32_t Width , int32_t Height, std::string Title);
    void terminate();

    bool isShouldClose();
    void SwapBuffers();
    void Viewport(int32_t Width , int32_t Height);


    void setShouldClose(bool new_state);

    void setCursorMod(uint32_t Flag);

    ~Window();
    Window();
};

