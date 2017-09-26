#ifndef HYPERBOREAN_SETTINGS_HPP_INCLUDED
#define HYPERBOREAN_SETTINGS_HPP_INCLUDED

#include <iostream>
#include <string>

namespace Hyperborean {
  // Global settings for the current game.
  struct Settings {
    ///////////////////////////////////////////////////////////////////////////
    // Attributes

    /// The title of the game
    std::string title;
    /// Game canvas dimensions in pixels
    int canvasWidth;
    int canvasHeight;
    /// Display dimensions in pixels
    int displayWidth;
    int displayHeight;
    /// Path to the manifest file
    std::string manifestPath;
    /// Path to the main script file
    std::string mainScriptPath;

    ///////////////////////////////////////////////////////////////////////////
    // Constants

    // Defined in cpp file
    static const std::string DEFAULT_GAME_TITLE;
    static const std::string DEFAULT_MANIFEST_PATH;
    static const std::string DEFAULT_MAIN_SCRIPT_PATH;

    static const int DEFAULT_CANVAS_WIDTH;
    static const int DEFAULT_CANVAS_HEIGHT;
    static const int DEFAULT_DISPLAY_WIDTH;
    static const int DEFAULT_DISPLAY_HEIGHT;

    ///////////////////////////////////////////////////////////////////////////
    // Life-cycle methods

    Settings() :
      title(DEFAULT_GAME_TITLE),
      canvasWidth(DEFAULT_CANVAS_WIDTH),
      canvasHeight(DEFAULT_CANVAS_HEIGHT),
      displayWidth(DEFAULT_DISPLAY_WIDTH),
      displayHeight(DEFAULT_DISPLAY_HEIGHT),
      manifestPath(DEFAULT_MANIFEST_PATH),
      mainScriptPath(DEFAULT_MAIN_SCRIPT_PATH) {}

    ///////////////////////////////////////////////////////////////////////////
    // Streams

    friend std::ostream& operator << (
      std::ostream& stream,
      const Settings& settings) {
      stream << "Settings[" << std::endl;
      stream << "  title='" << settings.title << "'," << std::endl;
      stream << "  canvas=" << settings.canvasWidth << "x" 
             << settings.canvasHeight  << "," << std::endl;
      stream << "  display=" << settings.displayWidth << "x"
             << settings.displayHeight << "," << std::endl;
      stream << "  manifest='" << settings.manifestPath << "'," << std::endl;
      stream << "  main='" << settings.mainScriptPath << "'" << std::endl;
      stream << "]";
      return stream;
    }
  };
}

#endif // HYPERBOREAN_SETTINGS_HPP_INCLUDED
