/**
* \file Transform.cpp
* \author Nicholas Ammann
* \date 2/27/2018
* \brief Member function definitions for Transform.
*/

#include "Core/Components/Transform.hpp"

namespace Elba
{
  Transform::Transform(Object* parent) : Component(parent)
  {
    // ask physics module to create transform object
  }

  void Transform::Initialize()
  {
  }
}