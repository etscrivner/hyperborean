#include "Application.hpp"

#include <cstdlib>
#include <iostream>

int Hyperborean::Application::Execute() {
  std::cout << "This is a test" << std::endl;
  return EXIT_SUCCESS;
}

int main() {
  Hyperborean::Application application;
  return application.Execute();
}
