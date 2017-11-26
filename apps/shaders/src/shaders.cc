#include <cmath>
#include <memory>

#include <libOlga/App.hh>
#include <libOlga/Color.hh>
#include <libOlga/Shader.hh>

static char *vertex_loc;
static char *fragment_loc;

struct Vertex {
  glm::vec3 loc;
  Color c;

  Vertex(glm::vec3 location, Color color) : loc(location), c(color) {}
};

class FirstShader : public App {
protected:
  void setup() override {
    // I haz a gl context here

    setBackgroundColor(Color(0.2f, 0.3f, 0.3f, 1.0f));

    s.loadNewShaders(Shader::Source::File, vertex_loc, fragment_loc);
    // s.loadNewShaders(Shader::Source::String, vertex, fragment);

    GLuint vbo, ebo;

    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_), indices_,
                 GL_STATIC_DRAW);

    ScopedShader ss{s};

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (const void *)offsetof(Vertex, loc));

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (const void *)offsetof(Vertex, c));

    // This is disabled when the VAO is disabled
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // These are not necessary due to VAO
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);

    // Everyone must enable the VAO, so this is not really needed
  }
  std::string appName() const override { return "shaders"; }

  void renderFrame(Double atTime, U64 frameNumber) override {
    float green = (sin(atTime) / 2.0f) + 0.5f;
    ScopedShader ss{s};
    s.setUniform("u_color", {0.001f * (frameNumber % 600), green, 1.0f, 1.0f});
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
  }

private:
  GLuint vao_;
  Color c;
  Shader s;

  // clang-format off
  static constexpr Size vertex_count_ = 3;
  const Vertex vertices_[vertex_count_] = {
    Vertex(glm::vec3( 0.5f, -0.5f, 0.0f), {1.0f, 0.0f, 0.0f}),
    Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), {0.0f, 1.0f, 0.0f}),
    Vertex(glm::vec3( 0.0f,  0.5f, 0.0f), {0.0f, 0.0f, 1.0f})
  };

  const GLuint indices_[3] = {
    0, 1, 2
  };
  // clang-format off

};

int main(int argc, char **argv) {

  if (argc < 3) return -1;
  vertex_loc = argv[1];
  fragment_loc = argv[2];

  const std::unique_ptr<App> app = std::make_unique<FirstShader>();
  app->configure(argc, argv);
  app->runMainLoop();
}
