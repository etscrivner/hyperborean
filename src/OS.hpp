#ifndef HYPERBOREAN_OS_HPP_INCLUDED
#define HYPERBOREAN_OS_HPP_INCLUDED

#include <string>

namespace Hyperborean {
  namespace OS {
    // Initialize the OS behavior of the application with the given path.
    //
    // Parameters:
    //   applicationPath - The path to the application (eg. argv[0])
    void Initialize(const std::string& applicationPath);

    // Cleanup and shutdown OS behavior of the application.
    void Shutdown();
  }
}

#endif // HYPERBOREAN_OS_HPP_INCLUDED
