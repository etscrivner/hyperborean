#include "Application.hpp"
#include "Errors.hpp"
#include "Log.hpp"
#include "OS.hpp"
#include "Settings.hpp"
#include "SettingsParser.hpp"
#include "Scripting/Environment.hpp"

#include <iostream>
#include <cstdlib>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
  #include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

int Hyperborean::Application::Execute(std::string applicationName,
                                      std::vector<std::string> arguments) {
  try {
    HBLOG_INFO("Starting %s", applicationName.c_str());
    InitializeSubsystems(applicationName);

    if (arguments.size() > 0) {
      HBLOG_INFO("Running script %s", arguments.front().c_str());

      Hyperborean::Scripting::Environment env("root");

      env.LoadFile(arguments.front());
      env.Execute("main");
    }

    SettingsParser settingsParser;
    Settings settings = settingsParser.FromFile("settings.lua");
    std::cout << settings << std::endl;
  } catch(Hyperborean::BaseError& error) {
    HBLOG_ERROR("Exception caught: %s", error.what());
    ShutdownSubsystems();
    return EXIT_FAILURE;
  }

  ShutdownSubsystems();
  return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Application::InitializeSubsystems(
  const std::string& applicationName)
{
  HBLOG_INFO("Initializing subsystems.");
  Hyperborean::OS::Initialize(applicationName);
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Application::ShutdownSubsystems()
{
  HBLOG_INFO("Shutting down subsystems.");
  Hyperborean::OS::Shutdown();
}
