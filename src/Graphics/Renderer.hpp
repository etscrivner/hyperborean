#ifndef HYPERBOREAN_GRAPHICS_RENDERER_HPP_INCLUDED
#define HYPERBOREAN_GRAPHICS_RENDERER_HPP_INCLUDED

#include "Graphics/Color.hpp"
#include "Graphics/RenderWindow.hpp"
#include "Graphics/Sprite.hpp"

#include <memory>

namespace Hyperborean {
  namespace Graphics {
    // Interface for rendering various sorts of primitives.
    class Renderer {
    public:
      Renderer(std::shared_ptr<RenderWindow> renderWindow);
      void Clear(const Hyperborean::Graphics::Color& clearColor);
      void DrawSprite(Hyperborean::Graphics::Sprite& sprite);
      void SwapBuffers();
    private:
      std::shared_ptr<RenderWindow> renderWindow_;
    };
  }
}

#endif // HYPERBOREAN_GRAPHICS_RENDERER_HPP_INCLUDED
