#include "Graphics/Sprite.hpp"
#include "Scripting/SpriteBinding.hpp"

#include <memory>

namespace SpriteTable {
  int Create(lua_State* state) {
    void* userData = lua_newuserdata(
      state, sizeof(std::shared_ptr<Hyperborean::Graphics::Sprite>));

    if (!userData) {
      return 0;
    }

    auto spritePtr = std::make_shared<Hyperborean::Graphics::Sprite>();
    new(userData) std::shared_ptr<Hyperborean::Graphics::Sprite>(spritePtr);

    luaL_getmetatable(state, "Sprite");
    lua_setmetatable(state, -2);

    return 1;
  }

  /////////////////////////////////////////////////////////////////////////////

  int Destroy(lua_State* state) {
    void* spritePtr = luaL_checkudata(state, 1, "Sprite");

    if (spritePtr) {
      auto sprite =
        static_cast<std::shared_ptr<Hyperborean::Graphics::Sprite>*>(spritePtr);
      sprite->reset();
    }

    return 0;
  }

  /////////////////////////////////////////////////////////////////////////////

  int GetX(lua_State* state) {
    void* spritePtr = luaL_checkudata(state, 1, "Sprite");

    if (spritePtr) {
      auto sprite =
        static_cast<std::shared_ptr<Hyperborean::Graphics::Sprite>*>(spritePtr);
      lua_pushnumber(state, (*sprite)->X());
    } else {
      return luaL_typerror(state, 1, "Sprite");
    }

    return 1;
  }

  /////////////////////////////////////////////////////////////////////////////

  int GetY(lua_State* state) {
    void* spritePtr = luaL_checkudata(state, 1, "Sprite");

    if (spritePtr) {
      auto sprite =
        static_cast<std::shared_ptr<Hyperborean::Graphics::Sprite>*>(spritePtr);
      lua_pushnumber(state, (*sprite)->Y());
    } else {
      return luaL_typerror(state, 1, "Sprite");
    }

    return 1;
  }
}

///////////////////////////////////////////////////////////////////////////////

const struct luaL_reg SpriteTableDefinition[] = {
  {"Create", SpriteTable::Create},
  {"GetX", SpriteTable::GetX},
  {"GetY", SpriteTable::GetY},
  {"__gc", SpriteTable::Destroy},
  {NULL, NULL}
};

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Scripting::SpriteBinding::Bind(
  Hyperborean::Scripting::Environment& context)
{
  context.AddClass("Sprite", SpriteTableDefinition);
}

