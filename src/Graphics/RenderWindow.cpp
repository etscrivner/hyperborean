#include "Errors.hpp"
#include "Log.hpp"
#include "RenderWindow.hpp"

#include <GLFW/glfw3.h>

struct Hyperborean::Graphics::RenderWindow::WindowData {
  GLFWwindow* window;
};

///////////////////////////////////////////////////////////////////////////////

Hyperborean::Graphics::RenderWindow::RenderWindow(
  const std::string& title,
  int width,
  int height) :
  windowData_(std::make_unique<Hyperborean::Graphics::RenderWindow::WindowData>())
{
  windowData_->window = glfwCreateWindow(
    width, height, title.c_str(), NULL, NULL
  );

  if (!windowData_->window)
  {
    throw Hyperborean::SubsystemInitializationError(
      "GLFW Error: Unable to initialize render window."
    );
  }

  glfwMakeContextCurrent(windowData_->window);
  InitializeCoordinateSystem(width, height);
}

///////////////////////////////////////////////////////////////////////////////

Hyperborean::Graphics::RenderWindow::~RenderWindow()
{
  // NOTE: We don't need to destroy window since termination will release
  //   resources for us.
  // glfwDestroyWindow(windowData_->window);
  windowData_->window = NULL;
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Graphics::RenderWindow::SwapBuffers()
{
  glfwSwapBuffers(windowData_->window);
}

///////////////////////////////////////////////////////////////////////////////

bool Hyperborean::Graphics::RenderWindow::ShouldClose() const
{
  return glfwWindowShouldClose(windowData_->window) == GLFW_TRUE;
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Graphics::RenderWindow::InitializeCoordinateSystem(
  int width, int height)
{
  int fbWidth;
  int fbHeight;

  glfwGetFramebufferSize(windowData_->window, &fbWidth, &fbHeight);
  glViewport(0, 0, fbWidth, fbHeight);

  double halfWidth = width / 2.0f;
  double halfHeight = height / 2.0f;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(
    -halfWidth, halfWidth, -halfHeight, halfHeight, 0.0f, 0.1f
  );
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
