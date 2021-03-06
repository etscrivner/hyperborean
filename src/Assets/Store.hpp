#ifndef HYPERBOREAN_ASSETS_STORE_INCLUDED_HPP
#define HYPERBOREAN_ASSETS_STORE_INCLUDED_HPP

#include "Assets/Asset.hpp"
#include "Log.hpp"

#include <map>
#include <memory>
#include <string>

namespace Hyperborean {
  namespace Assets {
    // Load store of assets from and asset manifest file.
    class Store {
    public:
      /////////////////////////////////////////////////////////////////////////
      // Methods

      // Adds a new asset with the given information to the asset store.
      //
      // Parameters:
      //   name - The name associated with the asset.
      //   path - The path to the asset file.
      //   type - The type of asset it is.
      //
      // Return: Pointer to the newly created asset.
      Asset*
      Add(const std::string& name,
          const std::string& path,
          const Asset::AssetType type);

      // Attempt to find the asset with the given name
      //
      // Parameters:
      //   name - The name of the asset in the asset store.
      //
      // Returns: Asset or NULL if an asset with the given name was not found.
      Asset* Find(const std::string& name);

      // Indicates whether or not an asset with the given name exists.
      //
      // Parameters:
      //   name - The name of the asset to search for.
      //
      // Returns: True if the asset exists in the store, false otherwise.
      bool Exists(const std::string& name) const;

      // Returns: The number of assets currently in the asset store.
      std::size_t Size() const;
    private:
      // Association of manifest name to loaded asset
      std::map<std::string, Asset> store_;
    };
  }
}

#endif // HYPERBOREAN_ASSETS_STORE_INCLUDED_HPP
