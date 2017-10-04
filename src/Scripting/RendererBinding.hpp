#ifndef HYPERBOREAN_SCRIPTING_RENDERER_BINDING_HPP_INCLUDED
#define HYPERBOREAN_SCRIPTING_RENDERER_BINDING_HPP_INCLUDED

#include "Scripting/Environment.hpp"

namespace Hyperborean {
  namespace Scripting {
    namespace RendererBinding {
      // Binds relevant Renderer interface methods to Lua.
      void Bind(Environment& context);
    }
  }
}

#endif // HYPERBOREAN_SCRIPTING_RENDERER_BINDING_HPP_INCLUDED
