#ifndef HYPERBOREAN_SCRIPTING_ENVIRONMENT_HPP_INCLUDED
#define HYPERBOREAN_SCRIPTING_ENVIRONMENT_HPP_INCLUDED

#include <stdexcept>
#include <string>

#include <lua.hpp>

namespace Hyperborean {
  namespace Scripting {
    ///////////////////////////////////////////////////////////////////////////
    // Scripting exceptions
    class ParseError : public std::runtime_error {
      using std::runtime_error::runtime_error;
    };

    class ExecutionError : public std::runtime_error {
      using std::runtime_error::runtime_error;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Wrapper around a Lua script execution environment.
    class Environment {
    public:
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
      //    local account = Account:new()
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
      // Variable accessors

      int GetInt(const char* key, const int defaultValue);
      bool GetBool(const char* key, const bool defaultValue);
      std::string GetString(const char* key, const std::string& defaultValue);
    private:
      /// The Lua execution environment global state
      lua_State* _luaState;
      /// The name of this execution environment, used for debugging
      std::string _name;
    };
  };
};

#endif // HYPERBOREAN_SCRIPTING_ENVIRONMENT_HPP_INCLUDED
