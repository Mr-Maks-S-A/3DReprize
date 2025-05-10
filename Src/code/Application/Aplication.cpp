#include <Application/Aplication.hpp>


Application& Application::get_app(){
    static Application app;
    return app;
};



Application::Application(){
    
    Win.initialize(1000,800,"Welkom");
    Event::init(Win.ptr_window);
    Cam = std::make_unique<Camera>(glm::vec3(0,0,1),glm::radians(90.0f));
};

void Application::main_Loop(){
    Shader Shader_Data ( "Resorces/Shaders/glsl/simple.vert"
                ,"Resorces/Shaders/glsl/simple.frag");

    Texture Texture_Data ("Resorces/Image/color grid.png"); 
    

    float   l_width_x = 1.0f,
            l_height_y = 1.0f,
            l_depth_z = 1.0f;
                    
  std::vector<uint32_t>attrib_size = {3, 2}; 
    std::vector<float> Vert_Coube {
        // positions                           // texture coords
            // front side
        -l_width_x, -l_height_y, -l_depth_z,   0.0f, 0.0f,
         l_width_x, -l_height_y, -l_depth_z,   1.0f, 0.0f,
         l_width_x,  l_height_y, -l_depth_z,   1.0f, 1.0f,

         l_width_x,  l_height_y, -l_depth_z,   1.0f, 1.0f,
        -l_width_x,  l_height_y, -l_depth_z,   0.0f, 1.0f,
        -l_width_x, -l_height_y, -l_depth_z,   0.0f, 0.0f,
         
            // back side
        -l_width_x, -l_height_y,  l_depth_z,   0.0f, 0.0f,
         l_width_x, -l_height_y,  l_depth_z,   1.0f, 0.0f,
         l_width_x,  l_height_y,  l_depth_z,   1.0f, 1.0f,

         l_width_x,  l_height_y,  l_depth_z,   1.0f, 1.0f,
        -l_width_x,  l_height_y,  l_depth_z,   0.0f, 1.0f,
        -l_width_x, -l_height_y,  l_depth_z,   0.0f, 0.0f,
            
            // left side
        -l_width_x,  l_height_y,  l_depth_z,   1.0f, 0.0f,
        -l_width_x,  l_height_y, -l_depth_z,   1.0f, 1.0f,
        -l_width_x, -l_height_y, -l_depth_z,   0.0f, 1.0f,

        -l_width_x, -l_height_y, -l_depth_z,   0.0f, 1.0f,
        -l_width_x, -l_height_y,  l_depth_z,   0.0f, 0.0f,
        -l_width_x,  l_height_y,  l_depth_z,   1.0f, 0.0f,

            // right side
         l_width_x,  l_height_y,  l_depth_z,   1.0f, 0.0f,
         l_width_x,  l_height_y, -l_depth_z,   1.0f, 1.0f,
         l_width_x, -l_height_y, -l_depth_z,   0.0f, 1.0f,

         l_width_x, -l_height_y, -l_depth_z,   0.0f, 1.0f,
         l_width_x, -l_height_y,  l_depth_z,   0.0f, 0.0f,
         l_width_x,  l_height_y,  l_depth_z,   1.0f, 0.0f,

            // bottom side
        -l_width_x, -l_height_y, -l_depth_z,   0.0f, 1.0f,
         l_width_x, -l_height_y, -l_depth_z,   1.0f, 1.0f,
         l_width_x, -l_height_y,  l_depth_z,   1.0f, 0.0f,

         l_width_x, -l_height_y,  l_depth_z,   1.0f, 0.0f,
        -l_width_x, -l_height_y,  l_depth_z,   0.0f, 0.0f,
        -l_width_x, -l_height_y, -l_depth_z,   0.0f, 1.0f,

           // up side
        -l_width_x,  l_height_y, -l_depth_z,   0.0f, 1.0f,
         l_width_x,  l_height_y, -l_depth_z,   1.0f, 1.0f,
         l_width_x,  l_height_y,  l_depth_z,   1.0f, 0.0f,

         l_width_x,  l_height_y,  l_depth_z,   1.0f, 0.0f,
        -l_width_x,  l_height_y,  l_depth_z,   0.0f, 0.0f,
        -l_width_x,  l_height_y, -l_depth_z,   0.0f, 1.0f,
        
    };
 

    Mesh square(Vert_Coube,attrib_size);
    



    
    float   LastTime    = glfwGetTime();
    float   deltaTime   = 0.0f ;

    float   Cam_rotate_X = 0.0f ,
            Cam_rotate_Y = 0.0f;
    

    glClearColor(0,1,0,1);

    glEnable(GL_DEPTH_TEST); 

    while(!Win.isShouldClose()){

        float currentTime = glfwGetTime();
        deltaTime = currentTime - LastTime;
        LastTime = currentTime;
        

        
        if(Event::justPressed(GLFW_KEY_ESCAPE)){
            Win.setShouldClose(true);
            std::cout<<"\t\nState Change";
        };

        if(Event::justPressed(GLFW_KEY_TAB)){
            Event::toogleCursor(Win);
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
        



    
        
        
        float Speed = 5;
        if(Event::pressed(GLFW_KEY_W)){
            Cam.get()->v_Psition += Cam.get()->v_FRONT * deltaTime * Speed;
        };
        if(Event::pressed(GLFW_KEY_S)){
            Cam.get()->v_Psition -= Cam.get()->v_FRONT * deltaTime * Speed;
        };

        if(Event::pressed(GLFW_KEY_SPACE)){
            Cam.get()->v_Psition += Cam.get()->v_UP * deltaTime * Speed;
        };
        if(Event::pressed(GLFW_KEY_LEFT_SHIFT)){
            Cam.get()->v_Psition -= Cam.get()->v_UP * deltaTime * Speed;
        };

        if(Event::pressed(GLFW_KEY_A)){
            Cam.get()->v_Psition -= Cam.get()->v_RIGHT * deltaTime * Speed;
        };
        if(Event::pressed(GLFW_KEY_D)){
            Cam.get()->v_Psition += Cam.get()->v_RIGHT * deltaTime * Speed;
        };


        Cam_rotate_X += (-Event::deltaY / Win.m_Height);
        Cam_rotate_Y += (-Event::deltaX / Win.m_Width);

        if(Cam_rotate_Y < -glm::radians(89.0f))Cam_rotate_Y = -glm::radians(89.0f);
        if(Cam_rotate_Y >  glm::radians(89.0f))Cam_rotate_Y =  glm::radians(89.0f);

        Cam.get()->m4_Rotation = glm::mat4(1.0f);
        Cam.get()->Rotate(Cam_rotate_X, Cam_rotate_Y, 0);


        Cam.get()->Update();

        
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        Shader_Data.use();
            glm::mat4x4 model(1.0f);
            // model = glm::translate(model, glm::vec3(-0.5f,0,0));
            model = glm::rotate(model,0.5f, glm::vec3(0,0,1));

            Shader_Data.uniform<glm::mat4x4>(glGetUniformLocation(Shader_Data.m_ID,"model"),model);
            Shader_Data.uniform<glm::mat4x4>(glGetUniformLocation(Shader_Data.m_ID,"prjview"),Cam.get()->get_Projection(Win.m_Width,Win.m_Height) * Cam.get()->get_View());
        
            Texture_Data.bind();
            square.draw();
        
        Win.SwapBuffers();
        Event::PullEvent();
    };
    
};

Application::~Application(){};