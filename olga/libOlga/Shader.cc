#include "Shader.hh"

#include "Types.hh"
#include "io/Utils.hh"

#include <glad/glad.h>

#include <iostream>

#define ENABLED (current_state_ == State::Enabled)

Shader::Shader() : current_state_(State::Invalid) {}

Shader::Shader(const String &vtxFilename, const String &fragFilename)
    : current_state_(State::Invalid) {
  initProgramFromFile(vtxFilename, fragFilename);
}

Shader::Shader(const Source &source, const String &vtx, const String &frag)
    : current_state_(State::Invalid) {
  if (source == Source::File) {
    initProgramFromFile(vtx, frag);
  } else {
    vertex_source_.assign(vtx);
    fragment_source_.assign(frag);
    compileAndLinkProgram();
  }
}

bool Shader::loadNewShaders(const Source &source, const String &vtx,
                            const String &frag) {
  if (source == Source::File) {
    initProgramFromFile(vtx, frag);
  } else {
    vertex_source_.assign(vtx);
    fragment_source_.assign(frag);
    compileAndLinkProgram();
  }

  if (current_state_ == State::Invalid)
    return false;
  else
    return true;
}

void Shader::initProgramFromFile(const String &vtxFilename,
                                 const String &fragFilename) {
  if (!io::ReadFile(vtxFilename, vertex_source_) ||
      !io::ReadFile(fragFilename, fragment_source_)) {
    // TODO (brian): Add logging
    return;
  }
  compileAndLinkProgram();
}

void Shader::compileAndLinkProgram() {

  GLHandle v = glCreateShader(GL_VERTEX_SHADER);
  GLHandle f = glCreateShader(GL_FRAGMENT_SHADER);

  const GLchar *vs = static_cast<const GLchar *>(vertex_source_.c_str());
  const GLchar *fs = static_cast<const GLchar *>(fragment_source_.c_str());
  glShaderSource(v, 1, &vs, NULL);
  glShaderSource(f, 1, &fs, NULL);

  {
    glCompileShader(v);
    int success;
    glGetShaderiv(v, GL_COMPILE_STATUS, &success);
    if (!success) {
      char infoLog[512];
      glGetShaderInfoLog(v, 512, NULL, infoLog);
      std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                << infoLog << std::endl;
    }
  }

  {
    glCompileShader(f);
    int success;
    glGetShaderiv(f, GL_COMPILE_STATUS, &success);
    if (!success) {
      char infoLog[512];
      glGetShaderInfoLog(f, 512, NULL, infoLog);
      std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                << infoLog << std::endl;
    }
  }

  program_ = glCreateProgram();

  glAttachShader(program_, v);
  glAttachShader(program_, f);

  {
    glLinkProgram(program_);
    int success;
    glGetProgramiv(program_, GL_LINK_STATUS, &success);
    if (!success) {
      char infoLog[512];
      glGetProgramInfoLog(program_, 512, NULL, infoLog);
      std::cerr << "ERROR::SHADER::PROGRAM::LINK_FAILED\n"
                << infoLog << std::endl;
    }
  }

  glDeleteShader(v);
  glDeleteShader(f);

  current_state_ = State::Ready;
}

void Shader::use() const {
  if (current_state_ == State::Ready) {
    glUseProgram(program_);
    current_state_ = State::Enabled;
  }
}

void Shader::disable() const {
  if (current_state_ == State::Enabled) {
    glUseProgram(0);
    current_state_ = State::Ready;
  }
}

GLLocation Shader::uniformHandle(const std::string &name) const {

  if (!ENABLED)
    return -1;

  auto location = location_cache_.find(name);
  if (location != std::end(location_cache_)) {
    return location->second;
  } else {
    GLLocation loc = glGetUniformLocation(program_, name.c_str());

    if (loc >= 0)
      location_cache_[name] = loc;

    return loc;
  }
}

void Shader::setUniform(GLLocation uniformLocation, bool value) const {
  if (ENABLED && uniformLocation >= 0)
    glUniform1i(uniformLocation, value);
}

void Shader::setUniform(GLLocation uniformLocation, int value) const {
  if (ENABLED && uniformLocation >= 0)
    glUniform1i(uniformLocation, value);
}

void Shader::setUniform(GLLocation uniformLocation, float value) const {
  if (ENABLED && uniformLocation >= 0)
    glUniform1f(uniformLocation, value);
}

void Shader::setUniform(GLLocation uniformLocation, Color value) const {
  if (ENABLED && uniformLocation >= 0) {
    glUniform4f(uniformLocation, value.r, value.g, value.b, value.a);
  }
}

void Shader::setUniform(const std::string &name, bool value) const {
  if (ENABLED)
    setUniform(uniformHandle(name), value);
}

void Shader::setUniform(const std::string &name, int value) const {
  if (ENABLED)
    setUniform(uniformHandle(name), value);
}

void Shader::setUniform(const std::string &name, float value) const {
  if (ENABLED)
    setUniform(uniformHandle(name), value);
}

void Shader::setUniform(const std::string &name, Color value) const {
  if (ENABLED)
    setUniform(uniformHandle(name), value);
}

Shader::State Shader::currentState() const { return current_state_; }
