#include "Application.hpp"

#include <cstdlib>
#include <iostream>

#include <lua.hpp>

int Hyperborean::Application::Execute(std::string applicationName,
                                      std::vector<std::string> arguments) {
  std::cout << "Initializing " << applicationName << std::endl;

  if (arguments.size() > 0) {
    lua_State* state = luaL_newstate();
    luaL_openlibs(state);

    luaL_loadfile(state, arguments.front().c_str());

    lua_pcall(state, 0, LUA_MULTRET, 0);
    lua_close(state);
  }

  return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////

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
