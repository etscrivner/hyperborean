#include "Assets/Store.hpp"

Hyperborean::Assets::Asset*
Hyperborean::Assets::Store::Add(
  const std::string& name,
  const std::string& path,
  const Hyperborean::Assets::Asset::AssetType type)
{
  auto result = store_.insert(
    std::pair<std::string, Hyperborean::Assets::Asset>(
      name, Asset(name, path, type)
    )
  );

  return &(result.first->second);
}

///////////////////////////////////////////////////////////////////////////////

bool Hyperborean::Assets::Store::Exists(const std::string& name) const
{
  return store_.find(name) != store_.end();
}

///////////////////////////////////////////////////////////////////////////////

std::size_t Hyperborean::Assets::Store::Size() const
{
  return store_.size();
}
