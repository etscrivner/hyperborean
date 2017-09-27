#include "OS/FileSystem.hpp"

#include <physfs.h>

bool Hyperborean::OS::FileSystem::Exists(
  const std::string& pathToFile)
{
  return PHYSFS_exists(pathToFile.c_str());
}

///////////////////////////////////////////////////////////////////////////////

Hyperborean::OS::File Hyperborean::OS::FileSystem::ReadFile(
  const std::string& pathToFile)
{
  if (!Exists(pathToFile))
  {
    throw Hyperborean::OS::FileSystemError("Cannot find file: " + pathToFile);
  }

  PHYSFS_file* file = PHYSFS_openRead(pathToFile.c_str());
  PHYSFS_sint64 fileSize = PHYSFS_fileLength(file);

  char* buffer = new char[fileSize];
  PHYSFS_sint64 lengthRead = PHYSFS_read(file, buffer, 1, fileSize);
  PHYSFS_close(file);

  if (lengthRead != fileSize)
  {
    throw Hyperborean::OS::FileSystemError("Unable to read whole file.");
  }

  Hyperborean::OS::File result;
  result.SetBuffer(buffer, fileSize);

  return result;
}
