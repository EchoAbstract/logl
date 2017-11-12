#ifndef APP_H
#define APP_H

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <cstdint>
#include <iostream>

class App {

public:
  void configure(int argc, char **argv);

  virtual ~App();

  void runMainLoop();

protected:
  GLFWwindow *window_;

  virtual void setup() = 0;
  virtual std::string appName() const { return "App"; }

  virtual void renderFrame(double atTime, int64_t frameNumber);

private:
  void init(int argc, char **argv);
};

#endif
