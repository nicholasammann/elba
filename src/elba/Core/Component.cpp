/**
* \file Component.cpp
* \author Nicholas Ammann
* \date 2/27/2018
* \brief Member function definitions for Component.
*/

#include "Core/Object.hpp"
#include "Core/Component.hpp"

namespace Elba
{
  Component::Component(Object* parent)
    : mParent(parent)
  {
  }
}