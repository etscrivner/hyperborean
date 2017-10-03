#ifndef HYPERBOREAN_GRAPHICS_TEXTURE_LOADER_HPP_INCLUDED
#define HYPERBOREAN_GRAPHICS_TEXTURE_LOADER_HPP_INCLUDED

#include "Texture.hpp"

#include <map>
#include <memory>
#include <string>

namespace Hyperborean {
  namespace Graphics {
    // Interface for loading texture images from files.
    class TextureLoader {
    public:
      // Loads a texture from the given file.
      //
      // Parameters:
      //   pathToTexture - Path to the texture file to be loaded.
      //
      // Returns: A pointer to the loaded texture.
      std::shared_ptr<Texture>
      Load(const std::string& pathToTexture);
    private:
      // Loads the texture at the given path from a file.
      //
      // Parameters:
      //   pathToTexture - Path to the texture file.
      //
      // Returns: A pointer to the loaded texture.
      std::shared_ptr<Texture> FromFile(const std::string& pathToTexture);

      // Mapping of texture paths onto loaded textures.
      std::map<std::string, std::weak_ptr<Texture>> textureCache_;
    };
  }
}

#endif // HYPERBOREAN_GRAPHICS_TEXTURE_LOADER_HPP_INCLUDED
