#ifndef APP_H
#define APP_H

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <cstdint>
#include <iostream>

#include "Color.hh"
#include "Types.hh"

class App {

public:
  void configure(int argc, char **argv);

  virtual ~App();

  void runMainLoop();

  Color backgroundColor() const;
  void setBackgroundColor(Color color);

protected:
  GLFWwindow *window_;

  virtual void setup() = 0;
  virtual std::string appName() const { return "App"; }

  virtual void renderFrame(Double atTime, U64 frameNumber);

private:
  void init(int argc, char **argv);

  Color backgroundColor_;

  U64 currentFrame_;
};

#endif
