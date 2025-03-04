
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <glad/glad.h> // Needs to be initialized with gladLoadGL() inuser's code

// #define GLM_FORCE_RADIANS 1
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>

#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <SDL3/SDL_opengl.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>

#include <iostream>




typedef struct {
  SDL_Window *window;
  SDL_GLContext glcontext;
} AppState;

static const struct {
  const char *key;
  const char *value;
} extended_metadata[] = {{SDL_PROP_APP_METADATA_URL_STRING, "NONE"},
                         {SDL_PROP_APP_METADATA_CREATOR_STRING, "Jarco"},
                         {SDL_PROP_APP_METADATA_COPYRIGHT_STRING, "None"},
                         {SDL_PROP_APP_METADATA_TYPE_STRING, "game"}};

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  if (!SDL_SetAppMetadata("Example OpenGlgame", "1.0", "OpenGlgame")) {
    return SDL_APP_FAILURE;
  }

  for (int32_t i = 0; i < SDL_arraysize(extended_metadata); ++i) {
    if (!SDL_SetAppMetadataProperty(extended_metadata[i].key,
                                    extended_metadata[i].value)) {
      return SDL_APP_FAILURE;
    }
  }

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    return SDL_APP_FAILURE;
  }

  AppState *as = (AppState *)SDL_calloc(1, sizeof(AppState));
  if (!as) {
    return SDL_APP_FAILURE;
  }

  *appstate = as;

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  // SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
  // SDL_GL_CONTEXT_PROFILE_CORE);

  // Request an OpenGL 4.6 context (should be core)
  const char *glsl_version = "#version 460";
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

  // Create window with graphics context
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  SDL_WindowFlags window_flags =
      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN;

  if (as->window =
          SDL_CreateWindow("SDL3/OpenGL Demo", 1600, 900, window_flags);
      as->window == nullptr)
    std::cout << "Error: SDL_CreateWindow(): \n" << SDL_GetError();

  SDL_SetWindowPosition(as->window, SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED);

  if (as->glcontext = SDL_GL_CreateContext(as->window);
      as->glcontext == nullptr)
    std::cout << "Error: SDL_GL_CreateContext(): \n" << SDL_GetError();

  // INITIALIZE GLAD:
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    std::cout << "Failed to initialize GLAD";

  SDL_GL_MakeCurrent(as->window, as->glcontext);
  SDL_GL_SetSwapInterval(1); // Enable vsync
  SDL_ShowWindow(as->window);

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsLight();

  // Setup Platform/Renderer backends
  ImGui_ImplSDL3_InitForOpenGL(as->window, as->glcontext);
  ImGui_ImplOpenGL3_Init(glsl_version);

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (appstate != nullptr) {

    ImGui_ImplSDL3_ProcessEvent(event);

    switch (event->type) {
    case SDL_EVENT_QUIT:
      return SDL_APP_SUCCESS;
      // case SDL_EVENT_KEY_DOWN:
      //   return handle_key_event_(ctx, event->key.scancode);
    }
  }
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  AppState *as = (AppState *)appstate;
  ImGuiIO &io = ImGui::GetIO();
  (void)io;

  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();

  // 1. Show the big demo window (Most of the sample code is in
  // ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear
  // ImGui!).
  if (show_demo_window)
    ImGui::ShowDemoWindow(&show_demo_window);

  // 2. Show a simple window that we create ourselves. We use a Begin/End pair
  // to create a named window.
  {
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!"
                                   // and append into it.

    ImGui::Text("This is some useful text."); // Display some text (you can
                                              // use a format strings too)
    ImGui::Checkbox(
        "Demo Window",
        &show_demo_window); // Edit bools storing our window open/close state
    ImGui::Checkbox("Another Window", &show_another_window);

    ImGui::SliderFloat("float", &f, 0.0f,
                       1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3(
        "clear color",
        (float *)&clear_color); // Edit 3 floats representing a color

    if (ImGui::Button("Button")) // Buttons return true when clicked (most
                                 // widgets return true when edited/activated)
      ++counter;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / io.Framerate, io.Framerate);
    ImGui::End();
  }

  // 3. Show another simple window.
  if (show_another_window) {
    ImGui::Begin(
        "Another Window",
        &show_another_window); // Pass a pointer to our bool variable (the
                               // window will have a closing button that will
                               // clear the bool when clicked)
    ImGui::Text("Hello from another window!");
    if (ImGui::Button("Close Me"))
      show_another_window = false;
    ImGui::End();
  }

  // Rendering
  ImGui::Render();
  glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
  glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
               clear_color.z * clear_color.w, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  SDL_GL_SwapWindow(as->window);

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  if (appstate != NULL) {
    AppState *as = (AppState *)appstate;

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    // SDL_DestroyRenderer(as->renderer);
    SDL_GL_DestroyContext(as->glcontext);
    SDL_DestroyWindow(as->window);
    SDL_free(as);
  }
}
