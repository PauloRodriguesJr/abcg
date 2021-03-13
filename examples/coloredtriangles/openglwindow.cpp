#include "openglwindow.hpp"

#include <fmt/core.h>
#include <imgui.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "abcg.hpp"

void OpenGLWindow::initializeGL() {
  const auto *vertexShader{R"gl(
    #version 410

  layout(location = 0) in vec2 inPosition; 
  layout(location = 1) in vec4 inColor;
  
  out vec4 fragColor;

void main(){
  gl_Position = vec4(inPosition, 0,1);
  fragColor = inColor;
}
)gl"};

  const auto *fragmentShader{R"gl(
    #version 410
    in vec4 fragColor;
  
    out vec4 outColor;

    void main(){ outColor = fragColor;}
    
)gl"};
  // Create shader program
  m_program = createProgramFromString(vertexShader, fragmentShader);

  // Clear window
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  // Start pseudo-random number generator
  auto seed{std::chrono::steady_clock::now().time_since_epoch().count()};
  m_randomEngine.seed(seed);
}
// Para o vertex shader entra incolor/inPosition-sai fragColor
// gl_Position -> inPosition,0,1 -> (x,y,0,1) homogêneas
// Cor repassada sem alterações
// Compilação/ ativação dos shaders -> "createProgramFromString"
// m_program é um int -  identifica o par frag/vert. shaders
// glUseProgram(m_program) para ativar
// glUseProgram(0) para apagar

void OpenGLWindow::paintGL() {
  setupModel();

  glViewport(0, 0, m_viewportWidth, m_viewportHeight);

  // ativa shader / vao
  glUseProgram(m_program);
  glBindVertexArray(m_vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);  // renderiza
  // (desenha um triangula na tela)

  // Desativa shader / vao
  glBindVertexArray(0);  // unbind vertexArrayObj
  glUseProgram(0);       // turn of the shader program
}

void OpenGLWindow::paintUI() {
  // Where imGui works
  abcg::OpenGLWindow::paintUI();
  // Our own ImGui widgets go below
  {
    auto widgetSize{ImVec2(250, 90)};  // Window Size and below, WindowPos
    ImGui::SetNextWindowPos(ImVec2(m_viewportWidth - widgetSize.x - 5,
                                   m_viewportHeight - widgetSize.y - 5));
    ImGui::SetNextWindowSize(widgetSize);
    // Window setup and begin
    auto windowFlags{ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar};
    ImGui::Begin(" ", nullptr, windowFlags);
    // edit vertex Colors
    auto colorEditFlags{ImGuiColorEditFlags_NoTooltip |
                        ImGuiColorEditFlags_NoPicker};

    ImGui::PushItemWidth(215);
    ImGui::ColorEdit3("v0", &m_vertexColors[0].x, colorEditFlags);
    ImGui::ColorEdit3("v1", &m_vertexColors[1].x, colorEditFlags);
    ImGui::ColorEdit3("v2", &m_vertexColors[2].x, colorEditFlags);
    ImGui::PopItemWidth();

    if (ImGui::Button("Press me!", ImVec2(100, 50))) {
      fmt::print("Button pressed.\n");
    }

    ImGui::End();
  }
}

void OpenGLWindow::resizeGL(int width, int height) {
  m_viewportWidth = width;
  m_viewportHeight = height;
  glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLWindow::terminateGL() {
  glDeleteProgram(m_program);
  glDeleteBuffers(1, &m_vboPositions);
  glDeleteBuffers(1, &m_vboColors);
  glDeleteVertexArrays(1, &m_vao);
}

// Chamado continuamente em paintGL
void OpenGLWindow::setupModel() {
  glDeleteBuffers(1, &m_vboPositions);
  glDeleteBuffers(1, &m_vboColors);
  glDeleteVertexArrays(1, &m_vao);

  // Create vertex positions
  std::uniform_real_distribution<float> rd(-1.5f, 1.5f);
  std::array positions{glm::vec2(rd(m_randomEngine), rd(m_randomEngine)),
                       glm::vec2(rd(m_randomEngine), rd(m_randomEngine)),
                       glm::vec2(rd(m_randomEngine), rd(m_randomEngine))};

  // Create vertex colors
  std::vector<glm::vec4> colors(0);
  colors.push_back(m_vertexColors[0]);
  colors.push_back(m_vertexColors[1]);
  colors.push_back(m_vertexColors[2]);

  // Generate VBO of positions
  glGenBuffers(1, &m_vboPositions);
  glBindBuffer(GL_ARRAY_BUFFER, m_vboPositions);
  glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions.data(),
               GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Generate VBO of colors
  glGenBuffers(1, &m_vboColors);
  glBindBuffer(GL_ARRAY_BUFFER, m_vboColors);
  glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec4),
               colors.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Get location of attributes in the program
  GLint positionAttribute{glGetAttribLocation(m_program, "inPosition")};
  GLint colorAttribute{glGetAttribLocation(m_program, "inColor")};
  // Create VAO
  glGenVertexArrays(1, &m_vao);

  // Bind vertex attributes to current VAO
  glBindVertexArray(m_vao);

  glEnableVertexAttribArray(positionAttribute);
  glBindBuffer(GL_ARRAY_BUFFER, m_vboPositions);

  glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glEnableVertexAttribArray(colorAttribute);
  glBindBuffer(GL_ARRAY_BUFFER, m_vboColors);
  glVertexAttribPointer(colorAttribute, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // End of binding to current VAO
  glBindVertexArray(0);
}
