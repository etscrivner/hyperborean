#ifndef HYPERBOREAN_GRAPHICS_RENDERER_HPP_INCLUDED
#define HYPERBOREAN_GRAPHICS_RENDERER_HPP_INCLUDED

#include "Graphics/Color.hpp"
#include "Graphics/Sprite.hpp"

namespace Hyperborean {
  namespace Graphics {
    // Interface for rendering various sorts of primitives.
    class Renderer {
    public:
      void Clear(const Hyperborean::Graphics::Color& clearColor);
      void DrawSprite(Hyperborean::Graphics::Sprite& sprite);
    };
  }
}

#endif // HYPERBOREAN_GRAPHICS_RENDERER_HPP_INCLUDED
