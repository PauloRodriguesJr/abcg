#ifndef OPENGLWINDOW_HPP_
#define OPENGLWINDOW_HPP_

#include <array>

#include "abcg.hpp"
#include "imgui.h"

class OpenGLWindow : public abcg::OpenGLWindow {
 protected:
  void initializeGL() override;
  void paintGL() override;
  void paintUI() override;
  void resizeGL(int width, int height) override;

 private:
  enum class GameState { Play, Draw, WinX, WinO };
  static const int m_N{3};  // Board size is m_N x m_N
  bool m_turn{true};
  ImFont* m_font{};
  GameState m_gameState{GameState::Play};
  bool m_turn{true};                      // true = X, false = O
  std::array<char, m_N * m_N> m_board{};  // '\0', 'X' or 'O'

  ImFont* m_font{};

  void checkBoard();
  void restart();
};

#endif