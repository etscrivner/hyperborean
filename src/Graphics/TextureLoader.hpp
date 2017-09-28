#ifndef HYPERBOREAN_GRAPHICS_TEXTURE_LOADER_HPP_INCLUDED
#define HYPERBOREAN_GRAPHICS_TEXTURE_LOADER_HPP_INCLUDED

#include "Texture.hpp"

#include <memory>
#include <string>

namespace Hyperborean {
  namespace Graphics {
    // Interface for loading texture images from files.
    namespace TextureLoader {
      // Loads a texture from the given file.
      //
      // Parameters:
      //   pathToTexture - Path to the texture file to be loaded.
      //
      // Returns: A pointer to the loaded texture.
      std::shared_ptr<Texture>
      FromFile(const std::string& pathToTexture);
    }
  }
}

#endif // HYPERBOREAN_GRAPHICS_TEXTURE_LOADER_HPP_INCLUDED
