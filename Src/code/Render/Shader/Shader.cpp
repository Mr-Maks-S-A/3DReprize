#include <Render/Shader/Shader.hpp>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>




Shader::Shader(const char* vertexPath, const char* fragmentPath){
// 1. retrieve the vertex/fragment source code from filePath
std::string vertexCode;
std::string fragmentCode;
std::ifstream vShaderFile;
std::ifstream fShaderFile;
// ensure ifstream objects can throw exceptions:
vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
try 
{
    // open files
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;
    // read file's buffer contents into streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();		
    // close file handlers
    vShaderFile.close();
    fShaderFile.close();
    // convert stream into string
    vertexCode   = vShaderStream.str();
    fragmentCode = fShaderStream.str();		
}
catch(std::ifstream::failure e)
{
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
}
const char* vShaderCode = vertexCode.c_str();
const char* fShaderCode = fragmentCode.c_str();

// 2. compile shaders
unsigned int vertex, fragment;
int success;
char infoLog[512];
   
// vertex Shader
vertex = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertex, 1, &vShaderCode, NULL);
glCompileShader(vertex);
// print compile errors if any
glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
if(!success)
{
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
};
  
// similiar for Fragment Shader
fragment = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(fragment, 1, &fShaderCode, NULL);
glCompileShader(fragment);
// print compile errors if any
glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
if(!success)
{
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
};
  
// shader Program
m_ID = glCreateProgram();
glAttachShader(m_ID, vertex);
glAttachShader(m_ID, fragment);
glLinkProgram(m_ID);
// print linking errors if any
glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
if(!success)
{
    glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
}
  
// delete the shaders as they're linked into our program now and no longer necessary
glDeleteShader(vertex);
glDeleteShader(fragment);

};
Shader::~Shader(){
    glDeleteProgram(m_ID);
};


void Shader::use(){
    glUseProgram(m_ID);
};


template<typename T>
    requires std::is_same<T, glm::vec2>::value 
          || std::is_same<T, glm::vec3>::value
          || std::is_same<T, glm::vec4>::value
          || std::is_same<T, glm::mat2>::value
          || std::is_same<T, glm::mat3>::value
          || std::is_same<T, glm::mat4>::value
void Shader::uniform(uint32_t value_id ,T valude_data){
    use();

   if constexpr (std::is_same<T, glm::vec2>::value){
        glUniform2f(value_id,valude_data);
    };
   if constexpr (std::is_same<T, glm::vec3>::value){
        glUniform3f(value_id,valude_data);
    };
   if constexpr (std::is_same<T, glm::vec4>::value){
        glUniform4f(value_id,valude_data);
    };

   if constexpr (std::is_same<T, glm::mat2>::value){
        glUniformMatrix2fv(value_id, 1, GL_FALSE, glm::value_ptr(valude_data));
    };
   if constexpr (std::is_same<T, glm::mat3>::value){
        glUniformMatrix3fv(value_id, 1, GL_FALSE, glm::value_ptr(valude_data));
    };
   if constexpr (std::is_same<T, glm::mat4>::value){
        glUniformMatrix4fv(value_id, 1, GL_FALSE, glm::value_ptr(valude_data));
    };
};