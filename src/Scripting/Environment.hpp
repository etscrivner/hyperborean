#ifndef HYPERBOREAN_SCRIPTING_ENVIRONMENT_HPP_INCLUDED
#define HYPERBOREAN_SCRIPTING_ENVIRONMENT_HPP_INCLUDED

#include <map>
#include <string>
#include <vector>

#include <lua.hpp>

#include "Errors.hpp"

// Macro for generating the boilerplate code for a module loading function.
//
// Parameters:
//   funcName - The name of the function
//   moduleName - The name of the module being loaded
//   moduleBinding - Array of structs mapping function names to function pointers.
#define GENERATE_LOAD_MODULE_FUNCTION(funcName, moduleName, moduleBinding) \
static int funcName(lua_State* state) { \
  luaL_register(state, moduleName, moduleBinding); \
  lua_pop(state, 1); \
  return 0;          \
}

///////////////////////////////////////////////////////////////////////////////

namespace Hyperborean {
  namespace Scripting {
    ///////////////////////////////////////////////////////////////////////////
    // Scripting exceptions

    class ParseError : public Hyperborean::BaseError {
      using Hyperborean::BaseError::BaseError;
    };

    class ExecutionError : public Hyperborean::BaseError {
      using Hyperborean::BaseError::BaseError;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Wrapper around a Lua script execution environment.
    class Environment {
    public:
      /////////////////////////////////////////////////////////////////////////
      // Type definitions

      // A group of table entry pairs
      typedef std::map<std::string, std::string> EntryMap;
      // Pair of table entry key to values in the associated table.
      typedef std::pair<std::string, EntryMap> TableEntries;

      /////////////////////////////////////////////////////////////////////////
      // Initializes an execution environment and assigns it a name.
      //
      // Parameters:
      //   name - The name to be given to the execution environment
      Environment(const std::string& name);

      /////////////////////////////////////////////////////////////////////////
      // Destroy execution environment.
      ~Environment();

      /////////////////////////////////////////////////////////////////////////
      // Loads the given string into the scripting environment.
      //
      // Parameters:
      //   scriptCode - The code to be loaded into the execution environment.
      //
      // Raises:
      //   Hyperborean::Scripting::ScriptParseError - If there was an issue
      //     parsing the script.
      void LoadString(const std::string& scriptCode);

      /////////////////////////////////////////////////////////////////////////
      // Loads the given file into the scripting environment for execution.
      //
      // Parameters:
      //   filePath - The path to the file to be loaded.
      // 
      // Raises:
      //   Hyperborean::Scripting::ScriptParseError - If there was an issue
      //     parsing the script.
      void LoadFile(const std::string& filePath);

      /////////////////////////////////////////////////////////////////////////
      // Executes whatever code is loaded in the current environment at the
      // global scope.
      //
      // Raises:
      //   Hyperborean::Scripting::ScriptExecutionError - If there was an error
      //     produced while running the script.
      void Execute();

      /////////////////////////////////////////////////////////////////////////
      // Executes the given function with the current environment. The function
      // is passed no parameters.
      //
      // Parameters:
      //   functionName - The name of the function to be executed.
      //
      // Raises:
      //   Hyperborean::Scripting::ScriptExecutionError - If there was an error
      //     produced while running the script.
      void Execute(const std::string& functionName);

      /////////////////////////////////////////////////////////////////////////
      // Retrieves the most recent error message from Lua along with a
      // (possibly empty) stack trace. If no error could successfully be
      // retrieved than a standard unknown error message is returned.
      //
      // Returns:
      //   The last error message from Lua along with a stack trace.
      const std::string GetErrorMessage();

      /////////////////////////////////////////////////////////////////////////
      // Adds a new metatable into the script execution environment with the
      // given name and associated methods.
      //
      // Parameters:
      //   className - The name to be given to the metatable.
      //   luaBinding - Methods on the new metatable.
      //
      // Returns:
      //   True if the class was added to the metatables, false otherwise.
      bool AddClass(const std::string& className,
                    const luaL_Reg* luaBinding);

      /////////////////////////////////////////////////////////////////////////
      // Adds an importable module into the script execution environment with
      // the given name. The function provided is used by Lua to initialize
      // the module.
      //
      // As an example, if we had an account object that we'd like to make
      // available, we can add the module to the execution environment as
      // follows:
      //
      //    env.AddModule("Account", accountLoadFunc);
      //
      // From a Lua script we can then import and execute the module:
      //
      //    require("Account")
      //    local account = Account.new()
      //
      // Parameters:
      //   moduleName - The name to be given to the module in scripts.
      //   loadModuleFunc - The function to be used when the module is loaded.
      //
      // Returns: 
      //   True if the module was added to the execution environment, false
      // otherwise.
      bool AddModule(const std::string& moduleName,
                     lua_CFunction loadModuleFunc);

      /////////////////////////////////////////////////////////////////////////
      // Value accessors

      // Returns: An integer value with the given key in the global namespace
      //   or the default if no such key is found.
      int GetInt(const char* key, const int defaultValue);
      // Returns: A boolean value with the given key in the global namespace or
      //   default value if no such key is found.
      bool GetBool(const char* key, const bool defaultValue);
      // Returns: A string value with the given key in the global namespace or
      //   default value if no such key is found.
      std::string GetString(const char* key, const std::string& defaultValue);

      /////////////////////////////////////////////////////////////////////////
      // Table accessors

      // Loads a global variable with the given name and ensures that it is a
      // table. This method is primarily used to load a table variable for
      // traversal.
      //
      // Parameters:
      //   tableName - The name of the global variable containing the table.
      void GetTable(const std::string& tableName);

      // Loads the value of a given key in a table. The key is expected to contain a table value
      // also.
      //
      // Parameters:
      //   key - The key of the table member to load.
      //
      // Returns: True if the value named by the key exists and is a table, false otherwise.
      bool OpenSubTable(const std::string& tableName);

      // Removes a subtable from the top of the stack. This will cause errors if called when a
      // sub-table is not atop the stack.
      void CloseSubTable();

      // Indicates whether or not the currently open table has remaining items in it.
      //
      // Returns: True if the table has remaining items, false otherwise.
      bool TableHasItems();

      // Returns a list of key to table entry key-value pairs for the next entry in the given table.
      //
      // This is used to parse the manifest file, but strives to be somewhat generic to allow other
      // similar files to be parsed also.
      //
      // Returns: A pair whose first item is the name of the key for the table entry and whose
      //   second item is a map of keys to values for all key-values in the named table.
      TableEntries GetNextTableEntry();
    private:
      /// The Lua execution environment global state
      lua_State* _luaState;
      /// The name of this execution environment, used for debugging
      std::string _name;
    };
  };
};

#endif // HYPERBOREAN_SCRIPTING_ENVIRONMENT_HPP_INCLUDED
