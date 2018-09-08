/**
* \file Component.cpp
* \author Nicholas Ammann
* \date 2/27/2018
* \brief Member function definitions for Component.
*/

#include "Elba/Core/Object.hpp"
#include "Elba/Core/Component.hpp"

namespace Elba
{
Component::Component(Object* parent)
  : mParent(parent)
  , mGuid()
{
}

GlobalKey Component::GetGuid() const
{
  return mGuid;
}

Object* Component::GetParent() const
{
  return mParent;
}
} // End of Elba namespace
