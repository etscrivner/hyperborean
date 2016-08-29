#include "Application.hpp"
#include "Log.hpp"
#include "Scripting/Environment.hpp"

#include <cstdlib>

int Hyperborean::Application::Execute(std::string applicationName,
                                      std::vector<std::string> arguments) {
  HBLOG_INFO("Starting %s", applicationName.c_str());

  if (arguments.size() > 0) {
    HBLOG_INFO("Running script %s", arguments.front().c_str());

    Hyperborean::Scripting::Environment env("root");

    env.LoadFile(arguments.front());
    env.Execute("main");
  }

  return EXIT_SUCCESS;
}
