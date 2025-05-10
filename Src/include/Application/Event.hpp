#pragma once

#include <vector>
#include <cstdint>

#define MOUSE_BUTTON_STEP 1024

class GLFWwindow;
class Window;


class Event{
    public:
    static Window window;
    static std::vector<bool> _keys;
    static std::vector<uint32_t> _frames;
    static uint32_t _current;
    static float deltaX;
    static float deltaY;
    static float x;
    static float y;
    static bool  _cursor_loked;
    static bool  _cursor_started;


    static uint32_t init(GLFWwindow* new_window);
    static void  PullEvent();

    static bool pressed(int keycode);
    static bool justPressed(int keycode);

    static bool mouse_pressed(int button);
    static bool mouse_justPressed(int button);

    static void toogleCursor(Window &target_window);

};

void key_callback(GLFWwindow * ptr_window 
        ,int key 
        ,int scancode 
        ,int action 
        ,int mode) ;

void mouse_button_callback(GLFWwindow * ptr_window 
            ,int button 
            ,int action 
            ,int mode) ;

void cursor_position_callback(GLFWwindow * ptr_window 
                ,double xpos 
                ,double ypos ) ;