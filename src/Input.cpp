#include "Input.hpp"

#include <GLFW/glfw3.h>

void Hyperborean::Input::Initialize()
{
  // N/A
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Input::Shutdown()
{
  // N/A
}

///////////////////////////////////////////////////////////////////////////////

bool Hyperborean::Input::TerminalEventReceived(
  const Hyperborean::Graphics::RenderWindow& renderWindow)
{
  return renderWindow.ShouldClose();
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Input::WaitForEventsTimeout(double timeoutSeconds)
{
  glfwWaitEventsTimeout(timeoutSeconds);
}
