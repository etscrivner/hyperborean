#ifndef HYPERBOREAN_GRAPHICS_SPRITE_HPP_INCLUDED
#define HYPERBOREAN_GRAPHICS_SPRITE_HPP_INCLUDED

#include "Graphics/Texture.hpp"
#include <memory>

namespace Hyperborean {
  namespace Graphics {
    class Sprite {
    public:
      /////////////////////////////////////////////////////////////////////////
      // Life-cycle methods

      Sprite();

      /////////////////////////////////////////////////////////////////////////
      // Methods

      void SetTexture(std::shared_ptr<Hyperborean::Graphics::Texture> texture);
      void SetPosition(int x, int y);

      int X() const;
      int Y() const;
      std::shared_ptr<Texture> Texture();
    private:
      /////////////////////////////////////////////////////////////////////////
      // Attributes

      int x_;
      int y_;
      std::shared_ptr<Hyperborean::Graphics::Texture> texture_;
    };
  }
}

#endif // HYPERBOREAN_GRAPHICS_SPRITE_HPP_INCLUDED
