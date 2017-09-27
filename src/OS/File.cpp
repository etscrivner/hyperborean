#include "File.hpp"
#include "Log.hpp"

#include <cstring>

Hyperborean::OS::File::File() :
  buffer_(NULL), sizeBytes_(0)
{ }

///////////////////////////////////////////////////////////////////////////////

Hyperborean::OS::File::~File()
{
  Reset();
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::OS::File::SetBuffer(
  const char* buffer, const std::size_t& sizeBytes)
{
  Reset();
  // NOTE: Need to add one to factor in null-terminator, otherwise we get junk as it searches to \0
  // char to terminate at.
  buffer_ = new char[sizeBytes+1];
  sizeBytes_ = sizeBytes;
  memcpy(buffer_, buffer, sizeof(char)*sizeBytes+1);
}

///////////////////////////////////////////////////////////////////////////////

const char* Hyperborean::OS::File::GetBuffer() const
{
  return buffer_;
}

///////////////////////////////////////////////////////////////////////////////

const std::size_t& Hyperborean::OS::File::GetSizeBytes() const
{
  return sizeBytes_;
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::OS::File::Reset()
{
  if (buffer_) {
    delete[] buffer_;
    buffer_ = NULL;
    sizeBytes_ = 0;
  }
}
