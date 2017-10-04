#ifndef HYPERBOREAN_SCRIPTING_SPRITE_BINDING_HPP_INCLUDED
#define HYPERBOREAN_SCRIPTING_SPRITE_BINDING_HPP_INCLUDED

#include "Scripting/Environment.hpp"

namespace Hyperborean {
  namespace Scripting {
    namespace SpriteBinding {
      // Binds relevant Sprite interface methods to Lua.
      void Bind(Environment& context);
    }
  }
}

#endif // HYPERBOREAN_SCRIPTING_SPRITE_BINDING_HPP_INCLUDED
