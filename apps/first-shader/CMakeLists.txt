cmake_minimum_required (VERSION 3.5.1)

project(first-shader)
set(project_name first-shader)


# Select C++14 dialect
set(CMAKE_CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

# file(GLOB PROJECT_HEADERS src/*.hh)
# file(GLOB PROJECT_SOURCES src/*.cc)

set(PROJECT_SOURCES
  src/first-shader.cc
)

set(PROJECT_HEADERS)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS} ${PROJECT_CONFIGS})


target_link_libraries(${PROJECT_NAME} assimp glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
                      BulletDynamics BulletCollision LinearMath Olga)
