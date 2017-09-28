#ifndef HYPERBOREAN_INPUT_HPP_INCLUDED
#define HYPERBOREAN_INPUT_HPP_INCLUDED

#include "Graphics/RenderWindow.hpp"

namespace Hyperborean {
  namespace Input {
    // Initializes the input subsystem.
    void Initialize();

    // Cleanup and shutdown the input subsystem.
    void Shutdown();

    // Indicates whether or not a terminal event was received
    bool TerminalEventReceived(
      const Hyperborean::Graphics::RenderWindow& renderWindow);

    // Waits for new events to process for the given number of seconds.
    //
    // Parameters:
    //   timeoutSeconds - Timeout in possibly fractional seconds.
    void WaitForEventsTimeout(double timeoutSeconds);
  }
}

#endif // HYPERBOREAN_INPUT_HPP_INCLUDED
