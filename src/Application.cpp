#include "Application.hpp"
#include "Assets/ManifestParser.hpp"
#include "Errors.hpp"
#include "Graphics.hpp"
#include "Graphics/RenderWindow.hpp"
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

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

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

    Hyperborean::OS::File file = Hyperborean::OS::FileSystem::ReadFile(
      "assets/player_sprite_sheet.png");

    ilInit();
    iluInit();
    ilutInit();
    ilutRenderer(ILUT_OPENGL);

    ILuint imageID;
    ilGenImages(1, &imageID);
    ilBindImage(imageID);
    ILboolean success = ilLoadL(
      IL_TYPE_UNKNOWN, (void*)file.GetBuffer(), file.GetSizeBytes());

    if (!success) {
      throw Hyperborean::BaseError("Unable to load image buffer");
    }

    ILinfo ImageInfo;
    iluGetImageInfo(&ImageInfo);
    if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
    {
      iluFlipImage();
    }

    success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
    if (!success)
    {
      ILenum error = ilGetError();
      throw Hyperborean::BaseError(iluErrorString(error));
    }

    GLuint textureID;

    // Generate a new texture
    glGenTextures(1, &textureID);

    // Bind the texture to a name
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture clamping method
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    // Set texture interpolation method to use linear interpolation (no MIPMAPS)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Specify the texture specification
    glTexImage2D(GL_TEXTURE_2D, 				// Type of texture
                 0,				// Pyramid level (for mip-mapping) - 0 is the top level
                 ilGetInteger(IL_IMAGE_FORMAT),	// Internal pixel format to use. Can be a generic type like GL_RGB or GL_RGBA, or a sized type
                 ilGetInteger(IL_IMAGE_WIDTH),	// Image width
                 ilGetInteger(IL_IMAGE_HEIGHT),	// Image height
                 0,				// Border width in pixels (can either be 1 or 0)
                 ilGetInteger(IL_IMAGE_FORMAT),	// Format of image pixel data
                 GL_UNSIGNED_BYTE,		// Image data type
                 ilGetData());			// The actual image data itself

    while (!Hyperborean::Input::TerminalEventReceived(renderWindow))
    {
      glClear(GL_COLOR_BUFFER_BIT);
      glLoadIdentity();
      glColor3f(1,1,1);
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, textureID);
      glBegin(GL_QUADS);
      glTexCoord2f(0, 0); glVertex3f(-320, -130, 0);
      glTexCoord2f(0, 1); glVertex3f(-320, 130, 0);
      glTexCoord2f(1, 1); glVertex3f(320, 130, 0);
      glTexCoord2f(1, 0); glVertex3f(320, -130, 0);
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
