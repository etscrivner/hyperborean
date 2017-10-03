#ifndef HYPERBOREAN_SCRIPTING_TEXTURE_BINDING_HPP_INCLUDED
#define HYPERBOREAN_SCRIPTING_TEXTURE_BINDING_HPP_INCLUDED

#include "Scripting/Environment.hpp"

namespace Hyperborean {
  namespace Scripting {
    namespace TextureBinding {
      // Binds relevant Texture interface methods to Lua.
      void Bind(Environment& context);
    }
  }
}

#endif // HYPERBOREAN_SCRIPTING_TEXTURE_BINDING_HPP_INCLUDED
