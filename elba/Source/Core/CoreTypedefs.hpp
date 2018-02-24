/**
* \file CoreTypedefs.hpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Typedefs to clean up some core types and containers.
*/

#pragma once

#include "Utilities/StdTypedefs.hpp"
#include "Utilities/GlobalKey.hpp"

#include "Core/CoreForwardDeclarations.hpp"

namespace Elba
{
  using ObjectMap = Map<GlobalKey, UniquePtr<Object>>;
}
