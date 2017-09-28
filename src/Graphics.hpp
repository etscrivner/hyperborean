#ifndef HYPERBOREAN_GRAPHICS_HPP_INCLUDED
#define HYPERBOREAN_GRAPHICS_HPP_INCLUDED

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
  #include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

namespace Hyperborean {
  namespace Graphics {
    // Initialize graphics sub-system
    void Initialize();

    // Cleanup and shutdown the graphics sub-system
    void Shutdown();
  }
}

#endif // HYPERBOREAN_GRAPHICS_HPP_INCLUDED
