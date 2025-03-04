#version 460 core
layout(location = 0) in vec3 position; // Устанавливаем позицию атрибута в 0

out vec4 vertexColor; // Передаем цвет во фрагментный шейдер

void main() {
  // Напрямую передаем vec3 в vec4
  gl_Position = vec4(position, 1.0); 
  
  // Устанавливаем значение выходной переменной в темно-красный цвет.
  vertexColor = vec4( 0.5f, 0.0f, 0.0f,1.0f);
}