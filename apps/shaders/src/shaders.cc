#include <cmath>
#include <memory>

#include <libOlga/App.hh>
#include <libOlga/Color.hh>

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

uniform vec4 u_color;

void main()
{
  FragColor = u_color;
}

)fragment";

class FirstShader : public App {
protected:
  void setup() override {
    // I haz a gl context here

    setBackgroundColor(Color(0.2f, 0.3f, 0.3f, 1.0f));

    // Compile shaders
    GLuint vtxShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    program_ = glCreateProgram();

    glShaderSource(vtxShader, 1, &vertex, NULL);
    glShaderSource(fragShader, 1, &fragment, NULL);

    {
      glCompileShader(vtxShader);
      int success;
      glGetShaderiv(vtxShader, GL_COMPILE_STATUS, &success);
      if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vtxShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
      }
    }

    {
      glCompileShader(fragShader);
      int success;
      glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
      if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
      }
    }

    glAttachShader(program_, vtxShader);
    glAttachShader(program_, fragShader);

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

    glDeleteShader(vtxShader);
    glDeleteShader(fragShader);

    uColorIndex_ = glGetUniformLocation(program_, "u_color");

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

    glUseProgram(program_);

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
  std::string appName() const override { return "shaders"; }

  void renderFrame(Double atTime, U64 frameNumber) override {
    float green = (sin(atTime) / 2.0f) + 0.5f;
    glUseProgram(program_);
    glUniform4f(uColorIndex_, 0.001f * (frameNumber % 600), green, 1.0f, 1.0f);
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
  }

private:
  GLuint vao_;
  GLuint program_;
  GLint uColorIndex_;
  Color c;

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
