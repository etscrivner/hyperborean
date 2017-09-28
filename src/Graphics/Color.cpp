#include "Graphics/Color.hpp"

const Hyperborean::Graphics::Color
Hyperborean::Graphics::Color::kBlack = Hyperborean::Graphics::Color(
  0.0f, 0.0f, 0.0f, 0.0f);

const Hyperborean::Graphics::Color
Hyperborean::Graphics::Color::kWhite = Hyperborean::Graphics::Color(
  1.0f, 1.0f, 1.0f, 0.0f);

///////////////////////////////////////////////////////////////////////////////

Hyperborean::Graphics::Color::Color(
  float red, float green, float blue, float alpha)
  : red(red), green(green), blue(blue), alpha(alpha)
{ }
