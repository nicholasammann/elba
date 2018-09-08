/**
* \file CoreTypedefs.hpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Typedefs to clean up some core types and containers.
*/

#pragma once

#include "Elba/Utilities/StdTypedefs.hpp"
#include "Elba/Utilities/GlobalKey.hpp"

#include "Elba/Core/CoreForwardDeclarations.hpp"

namespace Elba
{

using ObjectMap = Map<GlobalKey, UniquePtr<Object>>;
using ComponentMap = Map<GlobalKey, UniquePtr<Component>>;

} // End of Elba namespace
