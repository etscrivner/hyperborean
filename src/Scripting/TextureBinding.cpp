#include "Locator.hpp"
#include "Log.hpp"
#include "TextureBinding.hpp"

#include <memory>

namespace TextureTable {
  int Find(lua_State* state) {
    if (!lua_isstring(state, 1)) {
      return luaL_typerror(state, 1, "string");
    }

    const char* textureName = lua_tostring(state, 1);

    // Get asset path from asset store
    auto texture = Hyperborean::Locator::TextureLoader()->Load(
       textureName);
    // Add texture object pointer to meta table
    void* userData = lua_newuserdata(
      state, sizeof(std::shared_ptr<Hyperborean::Graphics::Texture>));

    if (!userData) {
      return 0;
    }

    new(userData) std::shared_ptr<Hyperborean::Graphics::Texture>(texture);

    luaL_getmetatable(state, "Texture");
    lua_setmetatable(state, -2);

    return 1;
  }

  /////////////////////////////////////////////////////////////////////////////

  int GetWidth(lua_State* state) {
    void* texturePtr = luaL_checkudata(state, 1, "Texture");

    if (texturePtr) {
      auto texture =
        static_cast<std::shared_ptr<Hyperborean::Graphics::Texture>*>(
          texturePtr);
      lua_pushnumber(state, (*texture)->Width());
    } else {
      return luaL_typerror(state, 1, "Texture");
    }

    return 1;
  }

  /////////////////////////////////////////////////////////////////////////////

  int GetHeight(lua_State* state) {
    void* texturePtr = luaL_checkudata(state, 1, "Texture");

    if (texturePtr)
    {
      auto texture =
        static_cast<std::shared_ptr<Hyperborean::Graphics::Texture>*>(
          texturePtr);

      lua_pushnumber(state, (*texture)->Height());
    }
    else
    {
      return luaL_typerror(state, 1, "Texture");
    }

    return 1;
  }

  /////////////////////////////////////////////////////////////////////////////

  int Destroy(lua_State* state) {
    void* texturePtr = luaL_checkudata(state, 1, "Texture");

    if (texturePtr) {
      auto texture =
        static_cast<std::shared_ptr<Hyperborean::Graphics::Texture>*>(
          texturePtr);
      texture->reset();
    }

    return 0;
  }
}

///////////////////////////////////////////////////////////////////////////////

const struct luaL_reg TextureTableDefinition[] = {
  {"Find", TextureTable::Find},
  {"GetWidth", TextureTable::GetWidth},
  {"GetHeight", TextureTable::GetHeight},
  {"__gc", TextureTable::Destroy},
  {NULL, NULL} // sentinel value
};

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Scripting::TextureBinding::Bind(
  Hyperborean::Scripting::Environment& context)
{
  context.AddClass("Texture", TextureTableDefinition);
}
