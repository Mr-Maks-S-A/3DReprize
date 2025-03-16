#version 460 core
layout(location = 0) in vec3 position; // Устанавливаем позицию атрибута в 0

uniform mat4 pvm;

out vec4 vertexColor;


void main() {
  // Напрямую передаем vec3 в vec4
  gl_Position = pvm * vec4(position, 1.0); 

}