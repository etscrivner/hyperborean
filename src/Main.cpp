#include "Application.hpp"

#include <string>
#include <vector>

#ifndef UNITTESTS

int main(int argc, char* argv[]) {
  // Retrieve the application name from the command-line
  std::string applicationName(argv[0]);

  // Convert all of the arguments provided
  size_t remainingItems = argc;
  std::vector<std::string> arguments;
  for (size_t index = 1; index < remainingItems; ++index) {
    arguments.push_back(argv[index]);
  }

  Hyperborean::Application application;
  return application.Execute(applicationName, arguments);
}

#endif
