#ifndef SHADER_HH
#define SHADER_HH

#include <unordered_map>

#include "Color.hh"
#include "Types.hh"

class Shader {
public:
  enum class State { Invalid, Ready, Enabled };

  enum class Source { String, File };

  Shader();
  Shader(const String &vtxFilename, const String &fragFilename);
  Shader(const Source &source, const String &vtx, const String &frag);

  bool loadNewShaders(const Source &source, const String &vtx,
                      const String &frag);

  void use() const;
  void disable() const;

  // utility uniform functions
  void setUniform(GLLocation uniformLocation, bool value) const;
  void setUniform(GLLocation uniformLocation, int value) const;
  void setUniform(GLLocation uniformLocation, float value) const;
  void setUniform(GLLocation uniformLocation, Color value) const;

  void setUniform(const String &name, bool value) const;
  void setUniform(const String &name, int value) const;
  void setUniform(const String &name, float value) const;
  void setUniform(const String &name, Color value) const;

  GLLocation uniformHandle(const String &name) const;

  State currentState() const;

private:
  GLHandle program_;

  String vertex_source_;
  String fragment_source_;

  // Internal state
  mutable State current_state_;
  mutable std::unordered_map<String, GLLocation> location_cache_;

  void initProgramFromFile(const String &vtxFilename,
                           const String &fragFilename);
  void compileAndLinkProgram();
};

// TODO (brian): This needs some thought...
struct ScopedShader {
  const Shader &shader_to_decomission_;

  ScopedShader(const Shader &shader) : shader_to_decomission_(shader) {
    shader_to_decomission_.use();
  }
  ~ScopedShader() { shader_to_decomission_.disable(); }
};
#endif
