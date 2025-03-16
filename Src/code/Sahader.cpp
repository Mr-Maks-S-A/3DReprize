#include <3D/Shader.hpp>

#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(std::string_view ShaderPath_Vertex,
               std::string_view ShaderPath_Fragment) {
  std::string CodeVertex;
  std::string CodeFragment;

//   std::string CodeGeometry;
//   std::string CodeTessControl;
//   std::string CodeTessEval;

  std::ifstream FileVertex;
  std::ifstream FileFragment;

  // ensure ifstream objects can throw exceptions:
  FileVertex.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  FileFragment.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    // open files
    FileVertex.open((std::string)ShaderPath_Vertex);
    FileFragment.open((std::string)ShaderPath_Fragment);
    std::stringstream StreamVertex, StreamFragment;
    // read file's buffer contents into streams
    StreamVertex << FileVertex.rdbuf();
    StreamFragment << FileFragment.rdbuf();
    // close file handlers
    FileVertex.close();
    FileFragment.close();
    // convert stream into string
    CodeVertex = StreamVertex.str();
    CodeFragment = StreamFragment.str();
  } catch (std::ifstream::failure &e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what()
              << std::endl;
  }

  const char *ptr_CodeVertex = CodeVertex.c_str();
  const char *ptr_CodeFragment = CodeFragment.c_str();
  // 2. compile shaders
  uint32_t vertex, fragment;
  // vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &ptr_CodeVertex, NULL);
  glCompileShader(vertex);
  checkCompileErrors(vertex, "VERTEX");
  // fragment Shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &ptr_CodeFragment, NULL);
  glCompileShader(fragment);
  checkCompileErrors(fragment, "FRAGMENT");
  // shader Program
  this->ID = glCreateProgram();
  glAttachShader(this->ID, vertex);
  glAttachShader(this->ID, fragment);
  glLinkProgram(this->ID);
  checkCompileErrors(this->ID, "PROGRAM");
  // delete the shaders as they're linked into our program now and no longer
  // necessary
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

Shader::~Shader() {}

void Shader::use() const { glUseProgram(this->ID); }

void Shader::checkCompileErrors(uint32_t shader, std::string type) {
  GLint success;
  GLchar infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      std::cout
          << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
          << infoLog
          << "\n -- --------------------------------------------------- -- "
          << std::endl;
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      std::cout
          << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
          << infoLog
          << "\n -- --------------------------------------------------- -- "
          << std::endl;
    }
  }
}

void Shader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
  glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string &name, float x, float y) const {
  glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
  glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const {
  glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
  glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string &name, float x, float y, float z,
                     float w) const {
  glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const {
  glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const {
  glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
  glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}
