#ifndef HYPERBOREAN_ASSETS_MANIFEST_PARSER_HPP_INCLUDED
#define HYPERBOREAN_ASSETS_MANIFEST_PARSER_HPP_INCLUDED

#include "Assets/Asset.hpp"
#include "Assets/Store.hpp"

#include <map>
#include <string>

namespace Hyperborean {
  namespace Assets {
    // Parses a Lua manifest file associating asset names and types with
    // various files. Names can be any arbitrary string, while paths must be
    // valid filesystem paths. The file format is as follows:
    //
    // manifest = {
    //   scripts = {
    //     ['main.lua'] = {
    //       path = "/path/to/main.lua"
    //     },
    //     ...
    //   },
    //   ...
    //   asset_type_name_N = {
    //     ...
    //   }
    // }
    class ManifestParser {
    public:
      /////////////////////////////////////////////////////////////////////////
      // Constants

      // The name of the global variable containing the manifest table.
      static const std::string ManifestTableName;
      // Static mapping of types to names of variables in manifest file
      static std::map<Asset::AssetType, std::string> TypeToManifestString;

      /////////////////////////////////////////////////////////////////////////
      // Methods

      Store FromFile(const std::string& pathToManifestFile);
    };
  }
}

#endif // HYPERBOREAN_ASSETS_MANIFEST_PARSER_HPP_INCLUDED
