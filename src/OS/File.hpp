#ifndef HYPERBOREAN_OS_FILE_HPP_INCLUDED
#define HYPERBOREAN_OS_FILE_HPP_INCLUDED

#include <cstddef>

namespace Hyperborean {
  namespace OS {
    // Represents a file loaded from the file system.
    class File {
    public:
      /////////////////////////////////////////////////////////////////////////
      // Life-cycle methods

      File();
      virtual ~File();

      /////////////////////////////////////////////////////////////////////////
      // Methods

      // Assigns the data contained in the buffer to this file object. This
      // method allocates a new buffer internally and copies the data from the
      // buffer given.
      //
      // Parameters:
      //   buffer - The buffer containing file data.
      //   sizeBytes - The size of the buffer in bytes.
      void SetBuffer(const char* buffer, const std::size_t& sizeBytes);

      // Retrieve the contents of the currently assigned buffer.
      //
      // Returns: The raw byte stream of the currently assigned buffer. NULL
      //   if no buffer is currently loaded.
      const char* GetBuffer() const;

      // Retrieve the size, in bytes, of the currently assigned buffer.
      //
      // Returns: The size of the currently assigned buffer in bytes or 0 if no
      //   buffer is loaded.
      const std::size_t& GetSizeBytes() const;
    private:
      // Deletes an allocated memory and resets the buffer to a clean slate.
      void Reset();

      // Raw file contents
      char* buffer_;
      // The size of the raw file contents in bytes
      std::size_t sizeBytes_;
    };
  }
}

#endif // HYPERBOREAN_OS_FILE_HPP_INCLUDED
