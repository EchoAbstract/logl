#include <memory>

#include <libOlga/App.hh>
#include <libOlga/Color.hh>
#include <libOlga/Shader.hh>

const char *vertex = R"vertex(
#version 410 core

layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)vertex";

const char *fragment = R"fragment(
#version 410 core

out vec4 FragColor;

void main()
{
  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}

)fragment";

class FirstShader : public App {
protected:
  void setup() override {
    // I haz a gl context here

    setBackgroundColor({0.2f, 0.3f, 0.3f, 1.0f});

    s_.loadNewShaders(Shader::Source::String, vertex, fragment);

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

    ScopedShader ss{s_};

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(Float),
                          (void *)0);

    // This is disabled when the VAO is disabled
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    // These are not necessary due to VAO
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);

    // Everyone must enable the VAO, so this is not really needed
  }
  std::string appName() const override { return "first-shader"; }

  void renderFrame(__attribute__((unused)) Double atTime,
                   __attribute__((unused)) U64 frameNumber) override {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    ScopedShader ss{s_};
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }

private:
  GLuint vao_;
  Shader s_;
  // clang-format off
  static constexpr Size vertex_count_ = 12;
  const Float vertices_[vertex_count_] = {
     0.5f,  0.5f, 0.0f, // top right
     0.5f, -0.5f, 0.0f, // bottom right

    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f  // top left
  };

  const GLuint indices_[6] = {
    0, 1, 3,
    1, 2, 3
  };
  // clang-format off

};

int main(int argc, char **argv) {
  const std::unique_ptr<App> app = std::make_unique<FirstShader>();
  app->configure(argc, argv);
  app->runMainLoop();
}
