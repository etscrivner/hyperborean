#include "Scripting/Environment.hpp"
#include "Log.hpp"

static int hello(lua_State*) {
  HBLOG_DEBUG("Hello from Lua");
  return 0;
}

static const struct luaL_reg luaBinding [] = {
  {"hello", hello},
  {NULL, NULL}
};

static int loadmodule_Account(lua_State* state) {
  const char* id = "Account";
  luaL_register(state, id, luaBinding);
  lua_pop(state, 1);
  return 0;
}

///////////////////////////////////////////////////////////////////////////////

Hyperborean::Scripting::Environment::Environment(const std::string& name)
  : _luaState(luaL_newstate()), _name(name)
{
  luaL_openlibs(_luaState);
  AddModule("Account", loadmodule_Account);
}

///////////////////////////////////////////////////////////////////////////////

Hyperborean::Scripting::Environment::~Environment()
{
  lua_close(_luaState);
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Scripting::Environment::LoadString(
  const std::string& scriptCode)
{
  if (luaL_loadstring(_luaState, scriptCode.c_str()) != 0) {
    throw Hyperborean::Scripting::ParseError(GetErrorMessage());
  }
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Scripting::Environment::LoadFile(const std::string& filePath)
{
  if (luaL_loadfile(_luaState, filePath.c_str()) != 0) {
    throw Hyperborean::Scripting::ParseError(GetErrorMessage());
  }
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Scripting::Environment::Execute()
{
  if (lua_pcall(_luaState, 0, LUA_MULTRET, 0) != 0) {
    throw Hyperborean::Scripting::ExecutionError(GetErrorMessage());
  }
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Scripting::Environment::Execute(
  const std::string& functionName)
{
  // First execute the script in order to define all functions
  Execute();

  // Now prepare the stack for the function call
  lua_getglobal(_luaState, functionName.c_str());

  if (!lua_isfunction(_luaState, -1)) {
    HBLOG_ERROR(
      "Expected function, found %s",
      lua_typename(_luaState, -1));
  }

  // Call the function on the top of the stack.
  if (lua_pcall(_luaState, 0, LUA_MULTRET, 0) != 0) {
    throw Hyperborean::Scripting::ExecutionError(GetErrorMessage());
  }
}

///////////////////////////////////////////////////////////////////////////////

const std::string Hyperborean::Scripting::Environment::GetErrorMessage()
{
  // Get the error message
  const char* errorMessage = lua_tostring(_luaState, -1);

  if (errorMessage == nullptr) {
    errorMessage = "Unrecognized Lua error";
  }

  std::string result(errorMessage);

  // Then get the traceback
  lua_getfield(_luaState, LUA_GLOBALSINDEX, "debug");
  if (!lua_istable(_luaState, -1)) {
    // Couldn't load the debugging library
    lua_pop(_luaState, 1); // pop the non-table
    return result;
  }

  lua_getfield(_luaState, -1, "traceback");

  if (!lua_isfunction(_luaState, -1)) {
    // If the traceback field doesn't exist
    lua_pop(_luaState, 2); // pop table and field
    return result;
  }

  lua_call(_luaState, 0, 1);
  const char* errorTrace = lua_tostring(_luaState, -1);

  if (errorTrace != nullptr) {
    result += "\n" + std::string(errorTrace);
  }

  return result;
}

///////////////////////////////////////////////////////////////////////////////

bool Hyperborean::Scripting::Environment::AddModule(
  const std::string& moduleName,
  lua_CFunction loadModuleFunc)
{
  // Push the `package.preload` table onto the stack.
  lua_getglobal(_luaState, "package");

  if (!lua_istable(_luaState, -1)) {
    HBLOG_ERROR(
      "Expected 'package' to be a table, found %s",
      lua_typename(_luaState, -1));
    return false;
  }

  lua_pushstring(_luaState, "preload");
  lua_gettable(_luaState, -2);

  if (!lua_istable(_luaState, -1)) {
    HBLOG_ERROR(
      "Expected 'package.preload' to be a table, found %s",
      lua_typename(_luaState, -1));
    return false;
  }

  // Essentially we do `package.preload[moduleName] = loadModuleFunc`
  lua_pushstring(_luaState, moduleName.c_str());
  lua_pushcfunction(_luaState, loadModuleFunc);
  lua_settable(_luaState, -3);

  // Cleanup
  lua_pop(_luaState, 2);

  return true;
}
