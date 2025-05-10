#include <Application/Event.hpp>
#include <Application/Aplication.hpp>

#include <iostream>

std::vector<bool> Event::_keys;
std::vector<uint32_t> Event::_frames;
uint32_t Event::_current = 0;

float Event::deltaX =0.0f;
float Event::deltaY =0.0f;
float Event::x      =0.0f;
float Event::y      =0.0f;

bool  Event::_cursor_loked      = false ;
bool  Event::_cursor_started    = false ;


void cursor_position_callback(GLFWwindow * ptr_window 
    ,double xpos 
    ,double ypos ) {
    if(Event::_cursor_loked){
        Event::deltaX += xpos - Event::x;
        Event::deltaY += ypos - Event::y;
    }
    else{
        Event::_cursor_started =true;
    }


    Event::x = xpos; 
    Event::y = ypos;


};


void mouse_button_callback(GLFWwindow * ptr_window 
    ,int button 
    ,int action 
    ,int mode) {

        if (action == GLFW_PRESS){
            Event::_keys[MOUSE_BUTTON_STEP+button] = true;
            Event::_frames[MOUSE_BUTTON_STEP+button] = Event::_current;
        }
        else if(action == GLFW_RELEASE){
            Event::_keys[MOUSE_BUTTON_STEP+button] = false;
            Event::_frames[MOUSE_BUTTON_STEP+button] = Event::_current;
        }
};


void key_callback(GLFWwindow * ptr_window 
    ,int key 
    ,int scancode 
    ,int action 
    ,int mode){
    if (action == GLFW_PRESS){
        Event::_keys[key] = true;
        Event::_frames[key] = Event::_current;
    }
    else if(action == GLFW_RELEASE){
        Event::_keys[key] = false;
        Event::_frames[key] = Event::_current;
    }

};


uint32_t Event::init(GLFWwindow* new_window){
    GLFWwindow* ptr_window = new_window;

    Event::_keys.resize (1032,false);
    Event::_frames.resize (1032, 0);

    std::cout<<"\n\tEvent init [keys.size : "<<Event::_keys.size()<<"]  value"<<Event::_keys[0]<<"\n";
    std::cout<<"\n\tEvent init [_frames.size : "<<Event::_frames.size()<<"]  value"<<Event::_frames[0]<<"\n";
   

    glfwSetKeyCallback(ptr_window, key_callback);
    glfwSetMouseButtonCallback(ptr_window, mouse_button_callback);
    glfwSetCursorPosCallback(ptr_window, cursor_position_callback);


    return EXIT_SUCCESS;
};


void Event::PullEvent(){
    _current++;
    Event::deltaX =0.0f;
    Event::deltaY =0.0f;

    glfwPollEvents();
};



bool Event::pressed(int keycode){
    if (keycode < 0 ||  keycode >= MOUSE_BUTTON_STEP)
    {
        return false;
    }
    
    return Event::_keys[keycode];     

}; 

bool Event::justPressed(int keycode){
    if (keycode < 0 ||  keycode >= MOUSE_BUTTON_STEP)
    {
        return false;
    }
    
    return Event::_keys[keycode] && Event::_frames[keycode] == _current;     

};


 bool Event::mouse_pressed(int button){
   
    return Event::_keys[MOUSE_BUTTON_STEP+button]; 

 };
 bool Event::mouse_justPressed(int button){
   
    return Event::_keys[MOUSE_BUTTON_STEP+button] && Event::_frames[MOUSE_BUTTON_STEP+button] == _current; 
 };


 void Event::toogleCursor(Window& target_window){
    _cursor_loked =! _cursor_loked ;
    target_window.setCursorMod(_cursor_loked ? GLFW_CURSOR_DISABLED: GLFW_CURSOR_NORMAL);
    
 };