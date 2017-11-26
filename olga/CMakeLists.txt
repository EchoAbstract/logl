# Define library. Only source files here!
project(libOlga VERSION 0.1)

# Select C++14 dialect
set(CMAKE_CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(libOlga/)

add_library(Olga SHARED
  ${VENDORS_SOURCES}

  # Base Library
  libOlga/App.cc
  libOlga/Color.cc
  libOlga/EventDispatcher.cc
  libOlga/Shader.cc

  # Geometry
  libOlga/geometry/Triangle.cc

  # IO
  libOlga/io/Utils.cc
  )

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
# target_include_directories(Olga PUBLIC
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libOlga>
#     $<INSTALL_INTERFACE:libOlga>
#     PRIVATE libOlga)

# If we have compiler requirements for this library, list them
# here
# target_compile_features(Olga
#     PUBLIC cxx_auto_type
#     PRIVATE cxx_variadic_templates)

# Depend on a library that we defined in the top-level file
# target_link_libraries(lib
#     boost
#     MyOtherLibrary)

target_link_libraries(Olga assimp glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
                      BulletDynamics BulletCollision LinearMath)

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS Olga EXPORT OlgaConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
# install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
# install(EXPORT OlgaConfig DESTINATION share/MyLibrary/cmake)

# This makes the project importable from the build directory
# export(TARGETS Olga FILE OlgaConfig.cmake)

# Every library has unit tests, of course
# add_executable(testlib
#     test/testlib.cpp)

# target_link_libraries(testlib
#     lib)

# add_test(testlib testlib)
