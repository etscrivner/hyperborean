#include "Errors.hpp"
#include "OS.hpp"
#include "Log.hpp"

#include <physfs.h>
#include <fmt/format.h>

std::string GetPhysFSErrorMessage() {
  PHYSFS_ErrorCode errorCode = PHYSFS_getLastErrorCode();
  return fmt::format(
    "PHYSFS error: Code {}: {}", errorCode, PHYSFS_getErrorByCode(errorCode)
  );
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::OS::Initialize(const std::string& applicationPath)
{
  HBLOG_INFO("OS::Initialize - %s", applicationPath.c_str());
  if (PHYSFS_init(applicationPath.c_str()) == 0)
  {
    throw Hyperborean::SubsystemInitializationError(GetPhysFSErrorMessage());
  }

  if (PHYSFS_mount(PHYSFS_getBaseDir(), "/", 1) == 0)
  {
    throw Hyperborean::SubsystemInitializationError(GetPhysFSErrorMessage());
  }
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::OS::Shutdown()
{
  HBLOG_INFO("OS::Shutdown");
  PHYSFS_deinit();
}
