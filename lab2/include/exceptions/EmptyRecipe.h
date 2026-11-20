#pragma once
#include <stdexcept>

/// Domain error: EmptyRecipe.
class EmptyRecipe : public std::runtime_error {
 public:
  EmptyRecipe() : std::runtime_error("EmptyRecipe") {}
};
