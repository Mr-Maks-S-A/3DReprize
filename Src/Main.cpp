#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <glad/glad.h> // Needs to be initialized with gladLoadGL() inuser's code


#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
// Optional. define TINYOBJLOADER_USE_MAPBOX_EARCUT gives robust triangulation. Requires C++11
//#define TINYOBJLOADER_USE_MAPBOX_EARCUT
#include "tiny_obj_loader.h"



#define GLM_FORCE_RADIANS 1
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <SDL3/SDL_opengl.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>

#include <iostream>
#include <cmath>

#include <3D/Shader.hpp>

// #====================================_00_=======================================

uint32_t VAO,VBO,EBO;

std::vector<float> coube_vertices;
// std::vector<uint32_t> coube_indices;

// std::vector<float> coube_vertices  = { -0.5f, -0.5f, 0.0f
//                                       ,0.5f, -0.5f, 0.0f
//                                       ,0.5f,  0.5f, 0.0f
//                                       ,-0.5f,  0.5f, 0.0f};
// std::vector<uint32_t> coube_indices = {0, 1, 2, 2, 3, 0};


glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
struct Camera{
  glm::vec3 m_Pos{0.0f, 0.0f, 3.0f}; // x,y,z
  glm::vec3 m_Target {0.0f, 0.0f, 0.0f};// x,y,z
  glm::vec3 m_Direction {glm::normalize(m_Pos - m_Target)};
  glm::vec3 m_Right {glm::normalize(glm::cross(up, m_Direction))};
  glm::vec3 m_Up {glm::cross(m_Direction, m_Right)};
} camera;


// glm::mat4 view {glm::lookAt(camera.m_Pos, camera.m_Target,up)};


typedef struct {
  SDL_Window *window;
  SDL_GLContext glcontext;

  Shader *Base;
} AppState;



static const struct {
  const char *key;
  const char *value;
} extended_metadata[] = {{SDL_PROP_APP_METADATA_URL_STRING, "NONE"},
                         {SDL_PROP_APP_METADATA_CREATOR_STRING, "Jarco"},
                         {SDL_PROP_APP_METADATA_COPYRIGHT_STRING, "None"},
                         {SDL_PROP_APP_METADATA_TYPE_STRING, "game"}};

// #====================================_00_=======================================

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  //=============================Initializate_Meta===========================
  if (!SDL_SetAppMetadata("3D_Project", "1.0", "Game?")) return SDL_APP_FAILURE;

  for (int32_t i = 0; i < SDL_arraysize(extended_metadata); ++i) {
    if (!SDL_SetAppMetadataProperty(extended_metadata[i].key,
                                    extended_metadata[i].value)) {
      return SDL_APP_FAILURE;
    }
  }
  //=============================Initializate_Meta===========================

  //=============================Initializate_SDL===========================
  if (!SDL_Init(SDL_INIT_VIDEO)) return SDL_APP_FAILURE;
  
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  // Request an OpenGL 4.6 context (should be core)
  const char *glsl_version = "#version 460";
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

  // Create window with graphics context
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  AppState *as = (AppState *)SDL_calloc(1, sizeof(AppState));
  if (!as) {
    return SDL_APP_FAILURE;
  }

  *appstate = as;

  SDL_WindowFlags window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE /* | SDL_WINDOW_HIDDEN*/;


  if (as->window =SDL_CreateWindow("3D_Project", 1600, 900, window_flags);
      as->window == nullptr)
    std::cout << "Error: SDL_CreateWindow(): \n" << SDL_GetError();

  SDL_SetWindowPosition(as->window, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);

  if (as->glcontext = SDL_GL_CreateContext(as->window);
      as->glcontext == nullptr)
    std::cout << "Error: SDL_GL_CreateContext(): \n" << SDL_GetError();

    // INITIALIZE GLAD:
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    std::cout << "Failed to initialize GLAD";

  SDL_GL_MakeCurrent(as->window, as->glcontext);
  SDL_GL_SetSwapInterval(1); // Enable vsync
  SDL_ShowWindow(as->window);
  //=============================Initializate_SDL===========================

   
   as->Base = new Shader("Resources/Shaders/UCamera_Vertex.glsl",
              "Resources/Shaders/UCamera_Fragment.glsl");


//======================================3D_model_Loading======================================





  // std::string inputfile = "Resources/Models/Base_Cube.obj";
  std::string inputfile = "Resources/Models/Base_Suzanne.obj";
  tinyobj::ObjReaderConfig reader_config;
  reader_config.mtl_search_path = "Resources/Models/"; // Path to material files

  tinyobj::ObjReader reader;

  if (!reader.ParseFromFile(inputfile, reader_config)) {
  if (!reader.Error().empty()) {
      std::cerr << "TinyObjReader: " << reader.Error();
  }
  exit(1);
}

if (!reader.Warning().empty()) {
  std::cout << "TinyObjReader: " << reader.Warning();
}


auto& attrib = reader.GetAttrib();
auto& shapes = reader.GetShapes();
auto& materials = reader.GetMaterials();




// Loop over shapes
for (size_t s = 0; s < shapes.size(); s++) {

//   for (long i = 0, cer = 0; i < shapes[s].mesh.indices.size(); ++i)
// {
//     coube_indices.push_back(shapes[s].mesh.indices[i].vertex_index);
//     std::cout<<shapes[s].mesh.indices[i].vertex_index /*<< ((cer%3) == 0) ? "\n":" "*/;
    
//     if(cer == 2) {std::cout<<std::endl; cer = 0;}
//     else ++cer;
// }
// std::cout<<"IndicesColVo :" << coube_indices.size()<<std::endl;
  // Loop over faces(polygon)
  size_t index_offset = 0;
  for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
    size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

    // Loop over vertices in the face.
    for (size_t v = 0; v < fv; v++) {
      //     attrib_t::vertices => 3 floats per vertex

      //      v[0]        v[1]        v[2]        v[3]               v[n-1]
      // +-----------+-----------+-----------+-----------+      +-----------+
      // | x | y | z | x | y | z | x | y | z | x | y | z | .... | x | y | z |
      // +-----------+-----------+-----------+-----------+      +-----------+
      tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
      tinyobj::real_t vx = attrib.vertices[3*size_t(idx.vertex_index)+0];
      tinyobj::real_t vy = attrib.vertices[3*size_t(idx.vertex_index)+1];
      tinyobj::real_t vz = attrib.vertices[3*size_t(idx.vertex_index)+2];


      // coube_indices.push_back(idx.vertex_index);
      coube_vertices.push_back(vx);
      coube_vertices.push_back(vy);
      coube_vertices.push_back(vz);

      std::cout<<"IDX :"<<idx.vertex_index<<"\n\tverts :"<<vx<<" "<<vy<<" "<<vz<<std::endl;

      // Check if `normal_index` is zero or positive. negative = no normal data

      //     attrib_t::normals => 3 floats per vertex

      //      n[0]        n[1]        n[2]        n[3]               n[n-1]
      // +-----------+-----------+-----------+-----------+      +-----------+
      // | x | y | z | x | y | z | x | y | z | x | y | z | .... | x | y | z |
      // +-----------+-----------+-----------+-----------+      +-----------+
      if (idx.normal_index >= 0) {
        tinyobj::real_t nx = attrib.normals[3*size_t(idx.normal_index)+0];
        tinyobj::real_t ny = attrib.normals[3*size_t(idx.normal_index)+1];
        tinyobj::real_t nz = attrib.normals[3*size_t(idx.normal_index)+2];
      }

      // Check if `texcoord_index` is zero or positive. negative = no texcoord data
      //     attrib_t::texcoords => 2 floats per vertex

      //     t[0]        t[1]        t[2]        t[3]               t[n-1]
      // +-----------+-----------+-----------+-----------+      +-----------+
      // |  u  |  v  |  u  |  v  |  u  |  v  |  u  |  v  | .... |  u  |  v  |
      // +-----------+-----------+-----------+-----------+      +-----------+
      if (idx.texcoord_index >= 0) {
        tinyobj::real_t tx = attrib.texcoords[2*size_t(idx.texcoord_index)+0];
        tinyobj::real_t ty = attrib.texcoords[2*size_t(idx.texcoord_index)+1];
      }

      // Optional: vertex colors
      //     attrib_t::colors => 3 floats per vertex(vertex color. optional)

      //      c[0]        c[1]        c[2]        c[3]               c[n-1]
      // +-----------+-----------+-----------+-----------+      +-----------+
      // | x | y | z | x | y | z | x | y | z | x | y | z | .... | x | y | z |
      // +-----------+-----------+-----------+-----------+      +-----------+
      // tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
      // tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
      // tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];
    }
    index_offset += fv;

    // per-face material
    shapes[s].mesh.material_ids[f];
  }
}





glGenVertexArrays(1, &VAO);

glGenBuffers(1, &VBO);
glBindBuffer(GL_ARRAY_BUFFER, VBO); 

// glGenBuffers(1, &EBO);
// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);




// 1. Привязываем VAO
glBindVertexArray(VAO);
    // 2. Копируем наши вершины в буфер для OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*coube_vertices.size(),&coube_vertices[0], GL_STATIC_DRAW);
    // // 3. Копируем наши индексы в в буфер для OpenGL
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*coube_indices.size(), &coube_indices[0], GL_STATIC_DRAW);
    // 3. Устанавливаем указатели на вершинные атрибуты
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  
// 4. Отвязываем VAO (НЕ EBO)
glBindVertexArray(0);



//======================================3D_model_Loading======================================

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {

if (appstate != nullptr) {

    switch (event->type) {
    case SDL_EVENT_QUIT:
      return SDL_APP_SUCCESS;
    }
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) { 
  AppState *as = (AppState *)appstate;
	 
   glm::mat4 projection;
	  float time = SDL_GetTicks() / 1000.f;
    int screenWidth, screenHeight;
    SDL_GetWindowSize(as->window, &screenWidth, &screenHeight);
    projection =  glm::perspective(45.0f, (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
	  
    
    // draw a color
	  float red = (std::sin(time) + 1) / 2.0;
	  float green = (std::sin(time / 2) + 1) / 2.0;
	  float blue = (std::sin(time) * 2 + 1) / 2.0;

    glm::mat4 view;
    float radius = 10.0f;
    camera.m_Pos.x= sin(time) * radius;
    camera.m_Pos.z= cos(time) * radius;
    view = glm::lookAt(camera.m_Pos, camera.m_Target,up);

    // glm::mat4 model;
    // model = glm::translate(model, glm::vec3(0.5f, -0.5f, 0.0f));
    // model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));  
    // model = glm::rotate(model,time * 50.0f, glm::vec3(0.0f, 0.0f, 1.0f));


    glm::mat4 pvm = projection*view/* *model */;

    uint32_t h_pvm = glGetUniformLocation(as->Base->ID, "pvm");
    glUniformMatrix4fv(h_pvm, 1, GL_FALSE, glm::value_ptr(pvm));






    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(red, green, blue, 1.f);

    as->Base->use();


    // glBindVertexArray(VAO);
    // glDrawElements(GL_TRIANGLES, coube_indices.size(), GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, coube_vertices.size());
    glBindVertexArray(0);


  SDL_GL_SwapWindow(as->window);
  
  return SDL_APP_CONTINUE; 
  }

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  AppState *as = (AppState *)appstate;
  if (as) {
    delete as->Base;
    SDL_GL_DestroyContext(as->glcontext);
    SDL_DestroyWindow(as->window);
    SDL_free(as);
  }
  SDL_Quit();
	SDL_Log("Application quit successfully!");
 
}
