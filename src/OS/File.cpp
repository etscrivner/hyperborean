#include "File.hpp"

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
  buffer_ = new char[sizeBytes];
  sizeBytes_ = sizeBytes;
  memcpy(buffer_, buffer, sizeBytes);
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
