# (c) Brian Wilson 2017
cmake_minimum_required (VERSION 3.5.1)

project(logl)
set(project_name logl)


# Select C++14 dialect
set(CMAKE_CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

# Subproject Options
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(vendor/glfw)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(vendor/assimp)

option(BUILD_BULLET2_DEMOS OFF)
option(BUILD_CPU_DEMOS OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_OPENGL3_DEMOS OFF)
option(BUILD_UNIT_TESTS OFF)
add_subdirectory(vendor/bullet)

# TODO(brian): Need to fix this to have better errors
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(vendor/assimp/include/
                    vendor/bullet/src/
                    vendor/glad/include/
                    vendor/glfw/include/
                    vendor/glm/
                    vendor/imgui/
                    vendor/stb/)

file(GLOB VENDORS_SOURCES vendor/glad/src/glad.c
                          vendor/imgui/imgui.cpp
                          # vendor/imgui/imgui_demo.cpp # Maybe add this?
                          vendor/imgui/imgui_draw.cpp)

# file(GLOB PROJECT_HEADERS src/*.hh)
# file(GLOB PROJECT_SOURCES src/*.cc)
file(GLOB PROJECT_SHADERS apps/common-res/shaders/*.comp # Not used
                          apps/common-res/shaders/*.frag
                          apps/common-res/shaders/*.geom # Not used
                          apps/common-res/shaders/*.vert)

file(GLOB PROJECT_TEXTURES  apps/common-res/textures/*)

file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          README.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

# source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
# source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Vendors" FILES ${VENDORS_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

add_subdirectory(olga)
include_directories(olga/)
add_subdirectory(apps)

# add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
#                                ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
#                                ${VENDORS_SOURCES})

# target_link_libraries(${PROJECT_NAME} assimp glfw
#                       ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
#                       BulletDynamics BulletCollision LinearMath)

file(COPY apps/common-res/shaders DESTINATION ${CMAKE_BINARY_DIR})
file(COPY apps/common-res/textures DESTINATION ${CMAKE_BINARY_DIR})
                      
