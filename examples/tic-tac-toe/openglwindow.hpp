#ifndef OPENGLWINDOW_HPP_
#define OPENGLWINDOW_HPP_

#include <array>

#include "abcg.hpp"

class OpenGLWindow : public abcg::OpenGLWindow {
 protected:
  void initializeGL() override;
  void paintGL() override;
  void paintUI() override;
  void resizeGL(int width, int height) override;

 private:
  std::array<float, 4> m_clearColor{0.906f, 0.910f, 0.918f, 0.0f};

  int m_viewportWidth{};
  int m_viewportHeight{};
};

#endif