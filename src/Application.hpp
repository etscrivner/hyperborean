#ifndef HYPERBOREAN_APPLICATION_HPP_INCLUDED
#define HYPERBOREAN_APPLICATION_HPP_INCLUDED

#include <string>
#include <vector>

namespace Hyperborean {
  class Application {
  public:
    int Execute(std::string applicationName,
                std::vector<std::string> arguments);
  };
}

#endif // HYPERBOREAN_APPLICATION_HPP_INCLUDED
