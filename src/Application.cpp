#include "Application.hpp"
#include "Log.hpp"
#include "Settings.hpp"
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
  HBLOG_INFO("Starting %s", applicationName.c_str());

  if (arguments.size() > 0) {
    HBLOG_INFO("Running script %s", arguments.front().c_str());

    Hyperborean::Scripting::Environment env("root");

    env.LoadFile(arguments.front());
    env.Execute("main");
  }

  Settings settings;
  std::cout << settings << std::endl;

  return EXIT_SUCCESS;
}
