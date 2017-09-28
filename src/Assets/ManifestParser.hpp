#ifndef HYPERBOREAN_ASSETS_MANIFEST_PARSER_HPP_INCLUDED
#define HYPERBOREAN_ASSETS_MANIFEST_PARSER_HPP_INCLUDED

#include "Assets/Asset.hpp"
#include "Assets/Store.hpp"

#include <map>
#include <memory>
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
    namespace ManifestParser {
      /////////////////////////////////////////////////////////////////////////
      // Methods

      // Loads a new manifest store from the given Lua file.
      //
      // Parameters:
      //   pathToManifestFile - Path to the manifest file.
      //
      // Returns: Pointer to the newly loaded asset store.
      Store
      FromFile(const std::string& pathToManifestFile);
    }
  }
}

#endif // HYPERBOREAN_ASSETS_MANIFEST_PARSER_HPP_INCLUDED
