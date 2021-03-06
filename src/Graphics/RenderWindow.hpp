#ifndef HYPERBOREAN_GRAPHICS_RENDER_WINDOW_HPP_INCLUDED
#define HYPERBOREAN_GRAPHICS_RENDER_WINDOW_HPP_INCLUDED

#include <string>
#include <memory>

namespace Hyperborean {
  namespace Graphics {
    // Represents a window into which things are rendered.
    class RenderWindow {
    public:
      /////////////////////////////////////////////////////////////////////////
      // Life-cycle methods

      // Initialize the render window.
      //
      // Parameters:
      //   title - The title ofthe window
      //   width - The width of the window in pixels (> 0)
      //   height - The height of the window in pixels (> 0)
      RenderWindow(const std::string& title, int width, int height);
      virtual ~RenderWindow();

      /////////////////////////////////////////////////////////////////////////
      // Methods

      // Swap buffers displaying the data that was written to the back frame
      // buffer.
      void SwapBuffers();

      // Indicates whether or not the render window was closed.
      bool ShouldClose() const;
    private:
      /////////////////////////////////////////////////////////////////////////
      // Methods

      // Initializes the coordinate system used by the application. We try to
      // set up a system as follows:
      //
      //                                   | (0, height/2)
      //                                   |
      //                                   |
      //                                   |
      //                                   | (0, 0)
      // (-width/2, 0) --------------------+-------------------- (width/2, 0)
      //                                   |
      //                                   |
      //                                   |
      //                                   |
      //                                   | (0, -height/2)
      void InitializeCoordinateSystem(int width, int height);

      /////////////////////////////////////////////////////////////////////////
      // Private attributes
      
      // Forward declaration for PImpl pattern
      struct WindowData;
      std::unique_ptr<WindowData> windowData_;
    };
  }
}

#endif // HYPERBOREAN_GRAPHICS_RENDER_WINDOW_HPP_INCLUDED
