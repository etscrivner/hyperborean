#include "Graphics.hpp"
#include "Graphics/Renderer.hpp"
#include "Log.hpp"

void Hyperborean::Graphics::Renderer::Clear(
  const Hyperborean::Graphics::Color& clearColor)
{
  glClearColor(
    clearColor.red, clearColor.green, clearColor.blue, clearColor.alpha
  );
  glClear(GL_COLOR_BUFFER_BIT);
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Graphics::Renderer::DrawSprite(
  Hyperborean::Graphics::Sprite& sprite)
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, sprite.Texture()->TextureID());

  int hWidth = sprite.Texture()->Width() / 2;
  int hHeight = sprite.Texture()->Height() / 2;

  glPushMatrix();

  glTranslatef(sprite.X(), sprite.Y(), 0);
  glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-hWidth, hHeight, 0);
    glTexCoord2f(0, 1); glVertex3f(-hWidth, -hHeight, 0);
    glTexCoord2f(1, 1); glVertex3f(hWidth, -hHeight, 0);
    glTexCoord2f(1, 0); glVertex3f(hWidth, hHeight, 0);
  glEnd();

  glPopMatrix();

  glDisable(GL_TEXTURE_2D);

}
