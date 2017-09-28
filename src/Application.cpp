#include "Application.hpp"
#include "Assets/ManifestParser.hpp"
#include "Errors.hpp"
#include "Graphics.hpp"
#include "Graphics/RenderWindow.hpp"
#include "Log.hpp"
#include "OS.hpp"
#include "Scripting/Environment.hpp"
#include "Settings.hpp"
#include "SettingsParser.hpp"

#include <iostream>
#include <cstdlib>

int Hyperborean::Application::Execute(std::string applicationName,
                                      std::vector<std::string> arguments) {
  try {
    HBLOG_INFO("Starting %s", applicationName.c_str());
    InitializeSubsystems(applicationName);

    if (arguments.size() > 0) {
      HBLOG_INFO("Running script %s", arguments.front().c_str());

      Hyperborean::Scripting::Environment env("root");

      env.LoadFile(arguments.front());
      env.Execute("main");
    }

    SettingsParser settingsParser;
    Settings settings = settingsParser.FromFile("settings.lua");
    std::cout << settings << std::endl;

    Hyperborean::Assets::ManifestParser manifestParser;
    manifestParser.FromFile(settings.manifestPath);

    Hyperborean::Graphics::RenderWindow renderWindow(
      settings.title, settings.displayWidth, settings.displayHeight
    );
  } catch(Hyperborean::BaseError& error) {
    HBLOG_ERROR("Exception caught: %s", error.what());
    ShutdownSubsystems();
    return EXIT_FAILURE;
  }

  ShutdownSubsystems();
  return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Application::InitializeSubsystems(
  const std::string& applicationName)
{
  HBLOG_INFO("Initializing subsystems.");
  Hyperborean::OS::Initialize(applicationName);
  Hyperborean::Graphics::Initialize();
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Application::ShutdownSubsystems()
{
  HBLOG_INFO("Shutting down subsystems.");
  Hyperborean::OS::Shutdown();
  Hyperborean::Graphics::Shutdown();
}
