#include "App.hh"
#include "EventDispatcher.hh"

#define STB_IMAGE_IMPLEMENTATION

void ErrorHandler(int code, const char *msg) {
  std::cout << "GLFW encountered an error " << code
            << " with the following information: \n\t" << msg << std::endl
            << std::endl;
  exit(-1);
}

void App::configure(int argc, char **argv) { init(argc, argv); }

void App::init(__attribute__((unused)) int argc,
               __attribute__((unused)) char **argv) {

  glfwSetErrorCallback(ErrorHandler);
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  window_ = glfwCreateWindow(1024, 768, "logl", nullptr, nullptr);
  glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glfwSetKeyCallback(window_, &EventDispatcher::key);
  glfwSetCursorPosCallback(window_, &EventDispatcher::cursor);
  glfwSetScrollCallback(window_, &EventDispatcher::scroll);
  glfwSetMouseButtonCallback(window_, &EventDispatcher::mouse);

  // Check for Valid Context
  if (window_ == nullptr) {
    ErrorHandler(-1, "Failed to Create OpenGL Context");
  }
  glfwMakeContextCurrent(window_);
  int width, height;
  glfwGetFramebufferSize(window_, &width, &height);
  gladLoadGL();

  glViewport(0, 0, width, height);

  // print out some info about the graphics drivers
  std::cout << appName() << " loaded:" << std::endl;
  std::cout << "\tOpenGL version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "\tGLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION)
            << std::endl;
  std::cout << "\tVendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "\tRenderer: " << glGetString(GL_RENDERER) << std::endl;

  this->setup();
}

void App::runMainLoop() {
  while (!glfwWindowShouldClose(window_)) {
    glfwPollEvents();
    this->renderFrame(0.0, 1);
  }
}

App::~App() { glfwTerminate(); }

void App::renderFrame(__attribute__((unused)) double atTime,
                      __attribute__((unused)) int64_t frameNumber) {}