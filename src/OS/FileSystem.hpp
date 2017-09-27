#ifndef HYPERBOREAN_OS_FILE_SYSTEM_HPP_INCLUDED
#define HYPERBOREAN_OS_FILE_SYSTEM_HPP_INCLUDED

#include "Errors.hpp"
#include "OS/File.hpp"

#include <string>

namespace Hyperborean {
  namespace OS {
    ///////////////////////////////////////////////////////////////////////////
    // Exceptions

    class FileSystemError : public Hyperborean::BaseError {
      using Hyperborean::BaseError::BaseError;
    };

    // Namespace encapsulating file system access
    namespace FileSystem {
      /////////////////////////////////////////////////////////////////////////
      // Methods

      // Check if the file at the given path exists.
      //
      // Parameters:
      //   pathToFile - Path to the file in the file system.
      //
      // Returns: True if the file exists, false otherwise.
      bool Exists(const std::string& pathToFile);

      // Read the file at the given path into a new file object.
      //
      // Parameters:
      //   pathToFile - Path to the file in the file system.
      //
      // Returns: The newly created file.
      // Raises:
      //   Hyperborean::OS::FileSystem::FileSystemError: If the give file does
      //     not exist.
      File ReadFile(const std::string& pathToFile);
    };
  }
}

#endif // HYPERBOREAN_OS_FILE_SYSTEM_HPP_INCLUDED
