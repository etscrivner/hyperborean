#ifndef HYPERBOREAN_SETTINGS_PARSER_HPP_INCLUDED
#define HYPERBOREAN_SETTINGS_PARSER_HPP_INCLUDED

#include <string>

#include "Settings.hpp"

namespace Hyperborean {
  // Parse settings from the given Lua file.
  class SettingsParser {
  public:
    ///////////////////////////////////////////////////////////////////////////
    // Loads settings fromt he given Lua file into a new settings object.
    //
    // Parameters:
    //   pathToSettingsFile - The filesystem path to the settings Lua file.
    //
    // Returns:
    //   A newly initailized settings object.
    Settings FromFile(const std::string& pathToSettingsFile);
  };

}

#endif // HYPERBOREAN_SETTINGS_PARSER_HPP_INCLUDED
