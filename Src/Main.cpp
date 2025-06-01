#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <format>
#include <vector>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

#include <glm/gtx/string_cast.hpp>

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}





auto main() -> std::int32_t {
  std::cout << "\n\t Hello World! \n\n";
  glm::vec2 rotate(1.f, 2.2f);
  glm::mat4 base_camera = camera(2.f , rotate);
  
  std::cout << glm::to_string(base_camera) << std::endl;

  std::cout << "\n\t Finalization \n\n";


  return EXIT_SUCCESS;
};
