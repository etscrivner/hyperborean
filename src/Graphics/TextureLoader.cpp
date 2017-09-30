#include "Graphics.hpp"
#include "OS/File.hpp"
#include "OS/FileSystem.hpp"
#include "TextureLoader.hpp"

#include <fmt/format.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::shared_ptr<Hyperborean::Graphics::Texture>
Hyperborean::Graphics::TextureLoader::FromFile(
  const std::string& pathToTexture)
{
  Hyperborean::OS::File textureFile =
    Hyperborean::OS::FileSystem::ReadFile(pathToTexture);

  int textureWidth;
  int textureHeight;
  int numTextureChannels;

  unsigned char* imageData = stbi_load_from_memory(
    (unsigned char*)textureFile.GetBuffer(),
    textureFile.GetSizeBytes(),
    &textureWidth,
    &textureHeight,
    &numTextureChannels,
    0
  );

  if (!imageData)
  {
    throw Hyperborean::ResourceError(
      fmt::format(
        "TextureLoader error: Unable to load texture file '{}'",
        pathToTexture
      )
    );
  }

  GLuint textureId;
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  GLint textureFormat = GL_RGB;

  if(numTextureChannels == 3)
  {
    textureFormat = GL_RGB;
  }
  else if(numTextureChannels == 4)
  {
    textureFormat = GL_RGBA;
  }

  glTexImage2D(
    GL_TEXTURE_2D, 0, textureFormat,
    textureWidth, textureHeight,
    0, textureFormat, GL_UNSIGNED_BYTE,
    imageData
  );
  glBindTexture(GL_TEXTURE_2D, 0);

  stbi_image_free(imageData);

  return std::make_shared<Hyperborean::Graphics::Texture>(
    textureId, textureWidth, textureHeight
  );
}
