#include "Errors.hpp"
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
}

///////////////////////////////////////////////////////////////////////////////

Hyperborean::Graphics::RenderWindow::~RenderWindow()
{
  glfwDestroyWindow(windowData_->window);
  windowData_->window = NULL;
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Graphics::RenderWindow::SwapBuffers()
{
  glfwSwapBuffers(windowData_->window);
}
