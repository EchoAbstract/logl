#ifndef GLFWEVENTDISPATCHER_HH
#define GLFWEVENTDISPATCHER_HH

#include <GLFW/glfw3.h>

class EventDispatcher {

public:
  static EventDispatcher &instance() {
    static EventDispatcher ourInstance;
    return ourInstance;
  }

  static void key(GLFWwindow *window, int key, int scancode, int action,
                  int mods);
  static void cursor(GLFWwindow *window, double xpos, double ypos);
  static void mouse(GLFWwindow *window, int button, int action, int mods);
  static void scroll(GLFWwindow *window, double xoffset, double yoffset);

private:
  EventDispatcher() = default;
  ~EventDispatcher() = default;
  EventDispatcher(const EventDispatcher &) = delete;
  EventDispatcher &operator=(const EventDispatcher &) = delete;
};

#endif
