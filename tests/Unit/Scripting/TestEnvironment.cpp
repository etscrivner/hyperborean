#include "Scripting/Environment.hpp"

#include "catch.hpp"

TEST_CASE("scripts can be loaded and executed", "[scripting]")
{
  Hyperborean::Scripting::Environment testEnvironment("test");
  const std::string testProgram = "name = \"test\"";

  SECTION("successfully loads program from string")
  {
    REQUIRE_NOTHROW(testEnvironment.LoadString(testProgram));
  }

  SECTION("successfully executes program from string")
  {
    testEnvironment.LoadString(testProgram);
    REQUIRE_NOTHROW(testEnvironment.Execute());
  }

  SECTION("raises exception if script has parsing errors")
  {
    REQUIRE_THROWS_AS(
      testEnvironment.LoadString("name = \"test"),
      Hyperborean::Scripting::ParseError
    );
  }

  SECTION("raises exception if script execution produces error")
  {
    testEnvironment.LoadString("error(\"bad stuff\")");
    REQUIRE_THROWS_AS(
      testEnvironment.Execute(),
      Hyperborean::Scripting::ExecutionError
    );
  }
}
