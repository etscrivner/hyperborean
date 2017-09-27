#ifndef HYPERBOREAN_ASSETS_ASSET_HPP_INCLUDED
#define HYPERBOREAN_ASSETS_ASSET_HPP_INCLUDED

#include <map>
#include <string>

namespace Hyperborean {
  namespace Assets {
    // Represents an asset loaded from an asset manifest file.
    class Asset {
    public:
      /////////////////////////////////////////////////////////////////////////
      // Constants

      // Enumeration of all allowed asset types.
      enum AssetType {
        kUnknown,
        kScript,
        kTexture,
        kCardinality
      };

      // Static mapping of asset types to names
      static std::map<AssetType, std::string> TypeToString;

      /////////////////////////////////////////////////////////////////////////
      // Life-cycle methods

      Asset(const std::string& name,
            const std::string& path,
            const AssetType& type);

      /////////////////////////////////////////////////////////////////////////
      // Methods

      // Returns: The name assigned to this asset.
      const std::string& Name() const;
      // Returns: The path of the asset file.
      const std::string& Path() const;
      // Returns: The type of this asset.
      AssetType Type() const;
      // Returns: The type of the given asset as a string.
      const std::string& TypeName() const;
    private:
      /////////////////////////////////////////////////////////////////////////
      // Attributes

      // The assigned name of the given asset
      std::string name_;
      // The full path of the asset file
      std::string path_;
      // The type of asset represented
      AssetType type_;
    };
  }
}

#endif // HYPERBOREAN_ASSETS_ASSET_HPP_INCLUDED
