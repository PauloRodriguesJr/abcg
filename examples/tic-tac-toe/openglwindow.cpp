#include "openglwindow.hpp"

#include <fmt/core.h>
#include <imgui.h>

#include <cppitertools/itertools.hpp>
#include <glm/mat3x3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <gsl/gsl>

#include "abcg.hpp"

void OpenGLWindow::initializeGL() {
  auto windowSettings{getWindowSettings()};
  fmt::print("Initial window size: {}x{}\n", windowSettings.width,
             windowSettings.height);
}

void OpenGLWindow::paintGL() { glClear(GL_COLOR_BUFFER_BIT); }

void OpenGLWindow::paintUI() {
  auto appWindowWidth{getWindowSettings().width};
  auto appWindowHeight{getWindowSettings().height};

  // "Tic-Tac-Toe" window
  {
    // Cover 100% of the application window
    auto windowWidth{appWindowWidth * 1.0f};
    auto windowHeight{appWindowHeight * 1.0f};
    ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight));
    ImGui::SetNextWindowPos(ImVec2((appWindowWidth - windowWidth) / 2,
                                   (appWindowHeight - windowHeight) / 2));
    auto flags{ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize};
    ImGui::Begin("Tic-Tac-Toe", nullptr, flags);

    std::string text;
    text = fmt::format(
        "Essa é uma mensagem: O jogo está começando O turno é de {}",
        m_turn ? 'X' : 'O');
    ImGui::Text("%s", text.c_str());
    ImGui::Spacing();
    ImGui::Spacing();

    auto gridHeight{windowHeight - 22 - 58 - (m_N * 10) - 58};

    // ImGui::PushFont(m_font);
    for (auto i : iter::range(m_N)) {
      ImGui::Columns(m_N);
      for (auto j : iter::range(m_N)) {
        auto offset{i * m_N + j};
        ImGui::Button("-", ImVec2(-1, gridHeight / m_N + 0.01 * offset));
        if (imGui::IsClicked) {
          // operar missão
        };
        ImGui::NextColumn();
      }
      ImGui::Columns(1);
      // ImGui::PopFont();

      ImGui::Spacing();
      ImGui::Spacing();
    }
    // 100x50 button
    // if (ImGui::Button("Press me!", ImVec2(100, 50))) {
    //   fmt::print("Button pressed.\n");
    // }
    // Nx50 button, where N is the remaining width available
    ImGui::Button("Restart Game", ImVec2(-1, 40));
    // See also IsItemHovered, IsItemActive, etc
    if (ImGui::IsItemClicked()) {
      fmt::print("Button pressed.\n");
    }

    // Window end
    ImGui::End();
  }
}

void OpenGLWindow::resizeGL(int width, int height) {
  m_viewportWidth = width;
  m_viewportHeight = height;
}
