

// #define GLM_ENABLE_EXPERIMENTAL
// #include <glm/glm.hpp>
// #include <glm/gtc/type_ptr.hpp>
// #include <glm/gtx/transform.hpp>
 
#include <iostream>
#include <Application/Aplication.hpp>


 
int32_t main()
{
    try
    {
       Application::get_app().main_Loop();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
 
    return EXIT_SUCCESS;
}

