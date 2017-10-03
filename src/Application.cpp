#include "Application.hpp"
#include "Assets/ManifestParser.hpp"
#include "Errors.hpp"
#include "Graphics.hpp"
#include "Graphics/Color.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/RenderWindow.hpp"
#include "Graphics/Sprite.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/TextureLoader.hpp"
#include "Input.hpp"
#include "Locator.hpp"
#include "Log.hpp"
#include "OS.hpp"
#include "OS/File.hpp"
#include "OS/FileSystem.hpp"
#include "Scripting/Environment.hpp"
#include "Settings.hpp"
#include "SettingsParser.hpp"

#include <iostream>
#include <memory>
#include <cstdlib>

int Hyperborean::Application::Execute(std::string applicationName,
                                      std::vector<std::string> arguments) {
  try {
    HBLOG_INFO("Starting %s", applicationName.c_str());
    InitializeSubsystems(applicationName);
    InitializeServices();

    if (!arguments.empty())
    {
      HBLOG_INFO("Got arguments");
    }

    SettingsParser settingsParser;
    Settings settings = settingsParser.FromFile("settings.lua");
    std::cout << settings << std::endl;

    auto assetStore = Hyperborean::Assets::ManifestParser::FromFile(
      settings.manifestPath);

    auto renderWindow = std::make_shared<Hyperborean::Graphics::RenderWindow>(
      settings.title, settings.displayWidth, settings.displayHeight);
    Hyperborean::Graphics::Renderer renderer(renderWindow);

    Hyperborean::Scripting::Environment environment("main");
    environment.LoadFile(settings.mainScriptPath);
    environment.Execute();

    while (!Hyperborean::Input::TerminalEventReceived(*renderWindow))
    {
      renderer.Clear(Hyperborean::Graphics::Color::kBlack);
      environment.Execute(settings.updateMethodName);
      renderer.SwapBuffers();
      Hyperborean::Input::WaitForEventsTimeout(0.0125);
    }
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
  Hyperborean::Input::Initialize();
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Application::ShutdownSubsystems()
{
  HBLOG_INFO("Shutting down subsystems.");
  Hyperborean::OS::Shutdown();
  Hyperborean::Graphics::Shutdown();
  Hyperborean::Input::Shutdown();
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Application::InitializeServices()
{
  Hyperborean::Locator::SetTextureLoader(
    std::make_shared<Hyperborean::Graphics::TextureLoader>());
}
