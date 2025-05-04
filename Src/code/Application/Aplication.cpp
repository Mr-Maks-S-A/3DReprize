#include <Application/Aplication.hpp>


Application& Application::get_app(){
    static Application app;
    return app;
};



Application::Application(){
    
    Win.initialize(1000,800,"Welkom");
    Event::init(Win.ptr_window);
};

void Application::main_Loop(){
    Shader SS ( "Resorces/Shaders/glsl/simple.vert"
                ,"Resorces/Shaders/glsl/simple.frag");

    Texture TT ("Resorces/Image/Test.png"); 
    

        std::vector<float> Vert = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
           -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
           -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
        };

        std::vector<uint32_t>indices = {  // Помните, что мы начинаем с 0!
            0, 1, 3,   // Первый треугольник
            1, 2, 3    // Второй треугольник
        };  

        uint32_t VAO,VBO,EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1,&VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,Vert.size()*sizeof(float), Vert.data(), GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Vert.size()*sizeof(uint32_t), indices.data(), GL_STATIC_DRAW); 
            // positions
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            
            // colors 
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1); 
            
            // texture coords
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);

        glBindVertexArray(0);


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

            SS.use();
            TT.bind();

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6 , GL_UNSIGNED_INT, 0);
            // glDrawArrays(GL_TRIANGLES,0,3);
            glBindVertexArray(0);

        Win.SwapBuffers();
       };

};

Application::~Application(){};