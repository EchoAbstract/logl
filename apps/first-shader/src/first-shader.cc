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

void main()
{
  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
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

    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);

    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);

    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_), triangle_, GL_STATIC_DRAW);

    glUseProgram(program_);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(Float),
                          (void *)0);

    // This is disabled when the VAO is disabled
    glEnableVertexAttribArray(0);

    // These are not necessary due to VAO
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glUseProgram(0);

    // Everyone must enable the VAO, so this is not really needed
    glBindVertexArray(0);
  }
  std::string appName() const override { return "first-shader"; }

  void renderFrame(__attribute__((unused)) Double atTime,
                   __attribute__((unused)) U64 frameNumber) override {
    glUseProgram(program_);
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glUseProgram(0);
  }

private:
  GLuint vbo_;
  GLuint vao_;
  GLuint program_;

  const Float triangle_[9] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                              0.0f,  0.0f,  0.5f, 0.0f};
};

int main(int argc, char **argv) {
  const std::unique_ptr<App> app = std::make_unique<FirstShader>();
  app->configure(argc, argv);
  app->runMainLoop();
}
