#include "Assets/ManifestParser.hpp"
#include "Errors.hpp"
#include "Log.hpp"
#include "OS/File.hpp"
#include "OS/FileSystem.hpp"
#include "Scripting/Environment.hpp"

#include <fmt/format.h>

const std::string ManifestTableName = "manifest";
const std::map<Hyperborean::Assets::Asset::AssetType, std::string>
TypeToManifestString = {
  {Hyperborean::Assets::Asset::kScript, "scripts"},
  {Hyperborean::Assets::Asset::kTexture, "textures"}
};

///////////////////////////////////////////////////////////////////////////////

Hyperborean::Assets::Store
Hyperborean::Assets::ManifestParser::FromFile(
  const std::string& pathToManifestFile)
{
  Hyperborean::Scripting::Environment manifest("manifest");
  Hyperborean::OS::File manifestFile = Hyperborean::OS::FileSystem::ReadFile(
    pathToManifestFile);
  manifest.LoadString(manifestFile.GetBuffer());
  manifest.Execute();

  Hyperborean::Assets::Store result;

  // Load the manifest table
  manifest.GetTable(ManifestTableName);
  // For each asset type
  for (auto it = TypeToManifestString.begin();
       it != TypeToManifestString.end(); it++) {
    auto entryTypeName = it->second;

    // Open the sub-table in the manifest with the asset type name
    if (manifest.OpenSubTable(entryTypeName)) {
      auto entryType = it->first;

      // For each entry in the sub-table
      while (manifest.TableHasItems()) {
        // Retrieve the entry and its associated key-value pairs
        auto entry = manifest.GetNextTableEntry();
        auto entryName = entry.first;
        auto items = entry.second;

        // Attempt to find a path entry as each manifest entry requires one.
        auto pathEntry = items.find("path");

        if (pathEntry == items.end()) {
          throw Hyperborean::ConstraintViolationError(
            fmt::format("Asset '{}' is missing 'path' entry.", entryName)
          );
        }

        std::string entryPath = pathEntry->second;

        // Add the newly loaded entry to our asset store.
        result.Add(entryName, entryPath, entryType);
      }
    }
    // Close the sub table we opened to clean up the stack.
    manifest.CloseSubTable();
  }

  return result;
}
