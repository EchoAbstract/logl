#include "EventDispatcher.hh"

void EventDispatcher::key(__attribute__((unused)) GLFWwindow *window,
                          __attribute__((unused)) int key,
                          __attribute__((unused)) int scancode,
                          __attribute__((unused)) int action,
                          __attribute__((unused)) int mods) {}

void EventDispatcher::cursor(__attribute__((unused)) GLFWwindow *window,
                             __attribute__((unused)) double xpos,
                             __attribute__((unused)) double ypos) {}

void EventDispatcher::mouse(__attribute__((unused)) GLFWwindow *window,
                            __attribute__((unused)) int button,
                            __attribute__((unused)) int action,
                            __attribute__((unused)) int mods) {}

void EventDispatcher::scroll(__attribute__((unused)) GLFWwindow *window,
                             __attribute__((unused)) double xoffset,
                             __attribute__((unused)) double yoffset) {}
