#ifndef HYPERBOREAN_LOG_HPP_INCLUDED
#define HYPERBOREAN_LOG_HPP_INCLUDED

#include <cstdarg>

///////////////////////////////////////////////////////////////////////////////
// Standard error logging macros

#define HBLOG_ERROR(fmt, ...) \
  Hyperborean::Log::Error(__FILE__, __LINE__, fmt, ## __VA_ARGS__)
#define HBLOG_WARNING(fmt, ...) \
  Hyperborean::Log::Warning(__FILE__, __LINE__, fmt, ## __VA_ARGS__)
#define HBLOG_INFO(fmt, ...) \
  Hyperborean::Log::Info(__FILE__, __LINE__, fmt, ## __VA_ARGS__)
#define HBLOG_DEBUG(fmt, ...) \
  Hyperborean::Log::Debug(__FILE__, __LINE__, fmt, ## __VA_ARGS__)

///////////////////////////////////////////////////////////////////////////////

namespace Hyperborean {
  namespace Log {
    ///////////////////////////////////////////////////////////////////////////
    // Logs a formatted message to standard output.
    //
    // Parameters:
    //   tag - The tag to append to the log message (ex. "error")
    //   file - The name of the file the message is logged at.
    //   line - The number of the line in the file the message is logged at.
    //   message - The formatted message to be logged.
    //   args - Any variadic arguments required for formatting the message.
    void Formatted(
      const char* tag,
      const char* file,
      const int line,
      const char* message,
      va_list args);

    ///////////////////////////////////////////////////////////////////////////
    // Pre-tagged logging methods. These will automatically attach their own
    // tag to the formatted message.
    void Error(const char* file, const int line, const char* fmt, ...);
    void Warning(const char* file, const int line, const char* fmt, ...);
    void Info(const char* file, const int line, const char* fmt, ...);
    void Debug(const char* file, const int line, const char* fmt, ...);
  }
}

#endif // HYPERBOREAN_LOG_HPP_INCLUDED
