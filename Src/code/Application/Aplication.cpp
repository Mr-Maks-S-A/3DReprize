#include <Application/Aplication.hpp>
#include <iostream>


Application& Application::get_app(){
    static Application app;
    return app;
};



Application::Application(){
    
    Win.initialize(1000,800,"Welkom");
    Event::init(Win.ptr_window);
};

void Application::main_Loop(){
    
    glClearColor(0,1,0,1);

    while(!Win.isShouldClose()){

        Event::PullEvent();
            if(Event::justPressed(GLFW_KEY_ESCAPE)){
                Win.setShouldClose(true);
                std::cout<<"\t\nState Change";
            };

            if(Event::justPressed(GLFW_KEY_D)){
                glClearColor(0,0,0,1);
                std::cout<<"\t\nState Change";
            };

            if(Event::mouse_justPressed(GLFW_MOUSE_BUTTON_1)){
                glClearColor(1,0.5,0,1);
                std::cout<<"\t\nChange color GLFW_MOUSE_BUTTON_1";
            };

            if(Event::mouse_justPressed(GLFW_MOUSE_BUTTON_2)){
                glClearColor(1,0,0,1);
                std::cout<<"\t\nChange color GLFW_MOUSE_BUTTON_2";
            };

            if(Event::mouse_justPressed(GLFW_MOUSE_BUTTON_3)){
                glClearColor(1,1,0,1);
                std::cout<<"\t\nChange color GLFW_MOUSE_BUTTON_3";
            };

            if(Event::mouse_justPressed(GLFW_MOUSE_BUTTON_4)){
                glClearColor(1,0,1,1);
                std::cout<<"\t\nChange color GLFW_MOUSE_BUTTON_4";
            };
            if(Event::mouse_justPressed(GLFW_MOUSE_BUTTON_5)){
                glClearColor(1,0.7,0.2,1);
                std::cout<<"\t\nChange color GLFW_MOUSE_BUTTON_5";
            };

            glClear(GL_COLOR_BUFFER_BIT);

        Win.SwapBuffers();
       };

};

Application::~Application(){};