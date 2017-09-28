#ifndef HYPERBOREAN_GRAPHICS_TEXTURE_HPP_INCLUDED
#define HYPERBOREAN_GRAPHICS_TEXTURE_HPP_INCLUDED

#include "Graphics.hpp"

#include <memory>

namespace Hyperborean {
  namespace Graphics {
    // Represents a texture image loaded from a file.
    class Texture
    {
    public:
      /////////////////////////////////////////////////////////////////////////
      // Life-cycle methods

      // Initialization.
      //
      // Parameters:
      //   textureId - The OpenGL ID of the given in-memory texture.
      //   width - The width of the texture image in pixels.
      //   height - The height of the texture image in pixels.
      Texture(GLuint textureId, int width, int height);
      virtual ~Texture();

      /////////////////////////////////////////////////////////////////////////
      // Methods

      // Returns: The width of the texture image in pixels.
      int Width() const;
      // Returns: The height of the texture image in pixels.
      int Height() const;
      // Returns: The OpenGL texture ID.
      GLuint TextureID() const;
    private:
      /////////////////////////////////////////////////////////////////////////
      // Private attributes

      GLuint textureId_;
      int textureWidth_;
      int textureHeight_;
    };
  }
}

#endif // HYPERBOREAN_GRAPHICS_TEXTURE_HPP_INCLUDED
