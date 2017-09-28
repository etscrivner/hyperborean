#include "Application.hpp"
#include "Assets/ManifestParser.hpp"
#include "Errors.hpp"
#include "Graphics.hpp"
#include "Graphics/RenderWindow.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/TextureLoader.hpp"
#include "Input.hpp"
#include "Log.hpp"
#include "OS.hpp"
#include "OS/File.hpp"
#include "OS/FileSystem.hpp"
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

    Hyperborean::Assets::ManifestParser::FromFile(settings.manifestPath);

    Hyperborean::Graphics::RenderWindow renderWindow(
      settings.title, settings.displayWidth, settings.displayHeight
    );

    std::unique_ptr<Hyperborean::Graphics::Texture>
    texture = Hyperborean::Graphics::TextureLoader::FromFile("grass_tile.jpg");

    int hWidth = texture->Width() / 2;
    int hHeight = texture->Height() / 2;

    while (!Hyperborean::Input::TerminalEventReceived(renderWindow))
    {
      glClear(GL_COLOR_BUFFER_BIT);

      glLoadIdentity();
      glColor3f(1,1,1);
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, texture->TextureID());
      glBegin(GL_QUADS);
      glTexCoord2f(0, 0); glVertex3f(-hWidth, hHeight, 0);
      glTexCoord2f(0, 1); glVertex3f(-hWidth, -hHeight, 0);
      glTexCoord2f(1, 1); glVertex3f(hWidth, -hHeight, 0);
      glTexCoord2f(1, 0); glVertex3f(hWidth, hHeight, 0);
      glEnd();
      glDisable(GL_TEXTURE_2D);

      renderWindow.SwapBuffers();
      Hyperborean::Input::WaitForEventsTimeout(0.6);
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
