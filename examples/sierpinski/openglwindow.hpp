#ifndef OPENGLWINDOW_HPP_
#define OPENGLWINDOW_HPP_

#include <array>
#include <glm/vec2.hpp>
#include <random>

#include "abcg.hpp"

class OpenGLWindow : public abcg::OpenGLWindow {
 protected:
  void initializeGL() override;
  void paintGL() override;
  void paintUI() override;
  void resizeGL(int width, int height) override;  // called when resize is done
  void terminateGL() override;                    //"Destructor"

 private:
  // Allocated GPU resources
  GLuint m_vao{};
  GLuint m_vboVertices{};
  GLuint m_program{};

  // This is useful to make OpenGL window with the same size as GL viewport
  int m_viewportWidth{};  // To get the window dimensions
  int m_viewportHeight{};

  // Random engine for C++ - #include <random> for this
  std::random_device m_randomDevice;
  std::default_random_engine m_randomEngine;

  // OpenGL mathematics -> vertex positions
  const std::array<glm::vec2, 3> m_points{glm::vec2(0, 1), glm::vec2(-1, -1),
                                          glm::vec2(1, -1)};
  glm::vec2 m_P{};  // point position

  void setupModel();  // Create GPU resources (called when the point is drawed)
};
#endif