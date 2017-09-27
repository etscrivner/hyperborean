#include "OS.hpp"
#include "Log.hpp"

#include <physfs.h>

void Hyperborean::OS::Initialize(const std::string& applicationPath)
{
  HBLOG_INFO("OS::Initialize - %s", applicationPath.c_str());
  PHYSFS_init(applicationPath.c_str());
  PHYSFS_addToSearchPath(PHYSFS_getBaseDir(), 1);
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::OS::Shutdown()
{
  HBLOG_INFO("OS::Shutdown");
  PHYSFS_deinit();
}
