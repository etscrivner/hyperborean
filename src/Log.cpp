#include "Log.hpp"

#include <chrono>
#include <cstdio>
#include <ctime>
#include <iomanip>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
// Macro used to simplify formatting messages with different tags.
//
// Parameters:
//   format - The message format
//   tag - The tag to use for the emitted message
//   file - The name of the file the message was logged at.
//   line - The number of the line the message was logged at.
#define FORMAT(format, tag, file, line) \
  do { \
    va_list args; \
    va_start(args, format); \
    Formatted(tag, file, line, format, args); \
    va_end(args); \
  } while(false)

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Log::Formatted(const char* tag,
                                 const char* file,
                                 const int line,
                                 const char* message,
                                 va_list args)
{
  auto now = std::chrono::system_clock::now();
  auto nowTime = std::chrono::system_clock::to_time_t(now);
  std::cout << tag 
            << " (" << std::put_time(std::localtime(&nowTime), "%c") << ")"
            << " [" << file << ":" << line << "] ";
  vprintf(message, args);
  std::cout << std::endl;
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Log::Error(const char* file,
                             const int line,
                             const char* fmt, ...)
{
  FORMAT(fmt, "ERROR", file, line);
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Log::Warning(const char* file,
                               const int line,
                               const char* fmt, ...)
{
  FORMAT(fmt, "WARNING", file, line);
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Log::Info(const char* file,
                            const int line,
                            const char* fmt, ...)
{
  FORMAT(fmt, "INFO", file, line);
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Log::Debug(const char* file,
                             const int line,
                             const char* fmt, ...)
{
  FORMAT(fmt, "DEBUG", file, line);
}
