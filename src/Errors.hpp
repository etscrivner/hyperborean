#ifndef HYPERBOREAN_ERRORS_HPP_INCLUDED
#define HYPERBOREAN_ERRORS_HPP_INCLUDED

#include <stdexcept>

namespace Hyperborean {
  // Base class for all exceptions generated by the game engine.
  class BaseError : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };
  // Raised whenever a necessary constraint is violated.
  class ConstraintViolationError : public BaseError {
    using BaseError::BaseError;
  };
}

#endif // HYPERBOREAN_ERRORS_HPP_INCLUDED
