#include "Errors.hpp"
#include "Graphics.hpp"
#include "Log.hpp"

#include <GLFW/glfw3.h>

void GLFWErrorCallback(int errorCode, const char* errorDescription)
{
  HBLOG_ERROR("GLFW Error: Code %d: %s", errorCode, errorDescription);
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Graphics::Initialize()
{
  HBLOG_INFO("Graphics::Initialize");

  glfwSetErrorCallback(GLFWErrorCallback);

  if (!glfwInit())
  {
    throw Hyperborean::SubsystemInitializationError(
      "GLFW Error: Initialization failed."
    );
  }
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Graphics::Shutdown()
{
  HBLOG_INFO("Graphics::Shutdown");

  glfwTerminate();
}
