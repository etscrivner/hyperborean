#include "Log.hpp"
#include "OS/File.hpp"
#include "OS/FileSystem.hpp"
#include "Scripting/Environment.hpp"
#include "Scripting/TextureBinding.hpp"

#include <map>

#include <fmt/format.h>

Hyperborean::Scripting::Environment::Environment(const std::string& name)
  : _luaState(luaL_newstate()), _name(name)
{
  luaL_openlibs(_luaState);
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
  auto file = Hyperborean::OS::FileSystem::ReadFile(filePath);
  LoadString(file.GetBuffer());
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
  // Now prepare the stack for the function call
  lua_getglobal(_luaState, functionName.c_str());

  if (!lua_isfunction(_luaState, -1)) {
    HBLOG_ERROR(
      "Expected function, found %s", lua_typename(_luaState, -1));
  }

  // Call the function on the top of the stack.
  if (lua_pcall(_luaState, 0, 0, 0) != 0) {
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

bool Hyperborean::Scripting::Environment::AddClass(
  const std::string& className,
  const luaL_Reg* luaBinding)
{
  const char* id = className.c_str();
  lua_newtable(_luaState);
  luaL_newmetatable(_luaState, id);
  luaL_register(_luaState, NULL, luaBinding);
  lua_pushliteral(_luaState, "__index");
  lua_pushvalue(_luaState, -2);
  lua_rawset(_luaState, -3);
  lua_setglobal(_luaState, id);

  return true;
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

///////////////////////////////////////////////////////////////////////////////

int Hyperborean::Scripting::Environment::GetInt(
  const char* key, const int defaultValue)
{
  lua_getfield(_luaState, LUA_GLOBALSINDEX, key);
  int result = luaL_optint(_luaState, -1, defaultValue);
  lua_pop(_luaState, 1);
  return result;
}

///////////////////////////////////////////////////////////////////////////////

bool Hyperborean::Scripting::Environment::GetBool(
  const char* key, const bool defaultValue)
{
  lua_getfield(_luaState, LUA_GLOBALSINDEX, key);
  if (lua_isboolean(_luaState, -1)) {
    return lua_toboolean(_luaState, -1);
  }
  return defaultValue;
}

///////////////////////////////////////////////////////////////////////////////

std::string Hyperborean::Scripting::Environment::GetString(
  const char* key, const std::string& defaultValue)
{
  lua_getfield(_luaState, LUA_GLOBALSINDEX, key);
  const char* result = luaL_optlstring(_luaState, -1, defaultValue.c_str(), NULL);
  lua_pop(_luaState, 1);
  return result;
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Scripting::Environment::GetTable(
  const std::string& tableName)
{
  lua_getglobal(_luaState, tableName.c_str());

  if (!lua_istable(_luaState, -1))
  {
    throw Hyperborean::Scripting::ParseError(
      fmt::format("Expected table name '{}'", tableName)
    );
  }
}

///////////////////////////////////////////////////////////////////////////////

bool Hyperborean::Scripting::Environment::OpenSubTable(
  const std::string& tableName)
{
  lua_pushstring(_luaState, tableName.c_str());
  lua_rawget(_luaState, -2);

  if (lua_istable(_luaState, -1)) {
    lua_pushnil(_luaState);
    return true;
  }

  return false;
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Scripting::Environment::CloseSubTable()
{
  lua_pop(_luaState, 1);
}

///////////////////////////////////////////////////////////////////////////////

bool Hyperborean::Scripting::Environment::TableHasItems()
{
  return (lua_next(_luaState, -2) != 0);
}

///////////////////////////////////////////////////////////////////////////////

Hyperborean::Scripting::Environment::TableEntries
Hyperborean::Scripting::Environment::GetNextTableEntry()
{
  const char* entryName = luaL_checkstring(_luaState, -2);
  if (!entryName)
  {
    throw Hyperborean::ConstraintViolationError(
      "Table contains non-string entry name."
    );
  }

  Hyperborean::Scripting::Environment::EntryMap pairs;
  lua_pushnil(_luaState);
  while (TableHasItems()) {
    std::string key = std::string(lua_tostring(_luaState, -2));
    std::string value = std::string(lua_tostring(_luaState, -1));

    pairs[key] = value;

    lua_pop(_luaState, 1);
  }

  lua_pop(_luaState, 1);

  TableEntries result(std::string(entryName), pairs);
  return result;
}
