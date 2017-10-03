#ifndef HYPERBOREAN_APPLICATION_HPP_INCLUDED
#define HYPERBOREAN_APPLICATION_HPP_INCLUDED

#include <string>
#include <vector>

namespace Hyperborean {
  // Entry-point for application-specific functionality.
  class Application {
  public:
    // Executes the application using command line arguments and configuration files provided.
    //
    // Parameters:
    //   applicationName - The name of the application (eg. argv[0])
    //   arguments - Additional command-line arguments provided
    //
    // Returns: Exit status of the application as return code.
    int Execute(std::string applicationName,
                std::vector<std::string> arguments);
  private:
    // Initializes all major sub-systems
    void InitializeSubsystems(const std::string& applicationName);
    // Cleanup and shutdown all major subsystems.
    void ShutdownSubsystems();

    // Initialize all services
    void InitializeServices();
  };
}

#endif // HYPERBOREAN_APPLICATION_HPP_INCLUDED
