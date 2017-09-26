#include "SettingsParser.hpp"
#include "Scripting/Environment.hpp"

Hyperborean::Settings Hyperborean::SettingsParser::FromFile(
  const std::string& pathToSettingsFile)
{
  // Load and run the given settings Lua file.
  Hyperborean::Scripting::Environment settings("settings");
  settings.LoadFile(pathToSettingsFile);
  settings.Execute();

  // Extract settings state from lua
  Settings result;
  result.title = settings.GetString("title", result.title);
  result.canvasWidth = settings.GetInt("canvasWidth", result.canvasWidth);
  result.canvasHeight = settings.GetInt("canvasWidth", result.canvasHeight);
  result.displayWidth = settings.GetInt("canvasWidth", result.displayWidth);
  result.displayHeight = settings.GetInt("canvasWidth", result.displayHeight);
  result.manifestPath = settings.GetString("manifestPath", result.manifestPath);
  result.mainScriptPath = settings.GetString("mainScriptPath", result.mainScriptPath);

  return result;
}
