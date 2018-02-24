/**
* \file StdTypedefs.hpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Typedefs to make standard library look nicer.
*/

#pragma once

#include <memory>

namespace ELBA
{
  template <typename T>
  using UniquePtr = std::unique_ptr<T>;

  template <typename T>
  using NewUnique = std::make_unique<T>;
}