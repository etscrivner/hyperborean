#include "Graphics.hpp"
#include "Texture.hpp"

Hyperborean::Graphics::Texture::Texture(
  GLuint textureId, int width, int height)
  : textureId_(textureId), textureWidth_(width), textureHeight_(height)
{ }

///////////////////////////////////////////////////////////////////////////////

Hyperborean::Graphics::Texture::~Texture()
{
  // NOTE: glDeleteTextures silently ignores uninitialized texture ids.
  glDeleteTextures(1, &textureId_);
}

///////////////////////////////////////////////////////////////////////////////

int Hyperborean::Graphics::Texture::Width() const
{
  return textureWidth_;
}

///////////////////////////////////////////////////////////////////////////////

int Hyperborean::Graphics::Texture::Height() const
{
  return textureHeight_;
}

///////////////////////////////////////////////////////////////////////////////

GLuint Hyperborean::Graphics::Texture::TextureID() const
{
  return textureId_;
}
