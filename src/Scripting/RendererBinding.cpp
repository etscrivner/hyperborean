#include "Locator.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Sprite.hpp"
#include "Scripting/RendererBinding.hpp"

namespace RendererTable {
  int DrawSprite(lua_State* state) {
    void* spritePtr = luaL_checkudata(state, 2, "Sprite");

    if (!spritePtr) {
      return luaL_typerror(state, 2, "Sprite");
    }

    auto sprite =
      static_cast<std::shared_ptr<Hyperborean::Graphics::Sprite>*>(spritePtr);
    auto renderer = Hyperborean::Locator::Renderer();

    renderer->DrawSprite(*sprite->get());

    return 0;
  }
}

///////////////////////////////////////////////////////////////////////////////

const struct luaL_reg RendererTableDefinition[] = {
  {"DrawSprite", RendererTable::DrawSprite},
  {NULL, NULL}
};

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Scripting::RendererBinding::Bind(
  Hyperborean::Scripting::Environment& context)
{
  context.AddClass("Renderer", RendererTableDefinition);
}
