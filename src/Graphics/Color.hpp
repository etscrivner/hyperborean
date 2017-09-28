#ifndef HYPERBOREAN_GRAPHICS_COLOR_HPP_INCLUDED
#define HYPERBOREAN_GRAPHICS_COLOR_HPP_INCLUDED

namespace Hyperborean {
  namespace Graphics {
    // Represents an RGBA color
    struct Color {
      /////////////////////////////////////////////////////////////////////////
      // Constants

      static const Color kBlack;
      static const Color kWhite;

      /////////////////////////////////////////////////////////////////////////
      // Attributes

      float red;
      float green;
      float blue;
      float alpha;

      /////////////////////////////////////////////////////////////////////////
      // Methods

      Color(float red, float green, float blue, float alpha);
    };
  }
}
#endif // HYPERBOREAN_GRAPHICS_COLOR_HPP_INCLUDED
