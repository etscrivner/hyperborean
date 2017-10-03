#ifndef HYPERBOREAN_LOCATOR_HPP_INCLUDED
#define HYPERBOREAN_LOCATOR_HPP_INCLUDED

#include "Errors.hpp"
#include "Graphics/TextureLoader.hpp"

#include <memory>

namespace Hyperborean {
  // Interface for locating various global registered services.
  class Locator
  {
  public:
    ///////////////////////////////////////////////////////////////////////////
    // TextureLoader

    static std::shared_ptr<Hyperborean::Graphics::TextureLoader>
    TextureLoader()
    {
      if (!textureLoader_)
      {
        throw Hyperborean::ConstraintViolationError(
            "Attempt to load missing TextureLoader instance.");
      }

      return textureLoader_;
    }

    static void SetTextureLoader(
      std::shared_ptr<Hyperborean::Graphics::TextureLoader> loader)
    {
      textureLoader_ = loader;
    }
  private:
    ///////////////////////////////////////////////////////////////////////////
    // Attributes

    static std::shared_ptr<Hyperborean::Graphics::TextureLoader>
      textureLoader_;
  };
}

#endif // HYPERBOREAN_LOCATOR_HPP_INCLUDED
