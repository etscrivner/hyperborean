#include "Assets/Asset.hpp"

std::map<Hyperborean::Assets::Asset::AssetType, std::string> 
 Hyperborean::Assets::Asset::TypeToString = {
  {Hyperborean::Assets::Asset::kUnknown, "unknown"},
  {Hyperborean::Assets::Asset::kScript, "scripts"},
};

///////////////////////////////////////////////////////////////////////////////

Hyperborean::Assets::Asset::Asset(
  const std::string& name,
  const std::string& path,
  const Hyperborean::Assets::Asset::AssetType& type)
  : name_(name), path_(path), type_(type)
{ }

///////////////////////////////////////////////////////////////////////////////

const std::string& Hyperborean::Assets::Asset::Name() const
{
  return name_;
}

///////////////////////////////////////////////////////////////////////////////

const std::string& Hyperborean::Assets::Asset::Path() const
{
  return path_;
}

///////////////////////////////////////////////////////////////////////////////

Hyperborean::Assets::Asset::AssetType
Hyperborean::Assets::Asset::Type() const
{
  return type_;
}

///////////////////////////////////////////////////////////////////////////////

const std::string& Hyperborean::Assets::Asset::TypeName() const {
  return TypeToString[type_];
}
