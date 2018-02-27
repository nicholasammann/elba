/**
* \file Model.cpp
* \author Nicholas Ammann
* \date 2/27/2018
* \brief Member function definitions for Model.
*/

#include "Core/Components/Model.hpp"

namespace Elba
{
  Model::Model(Object* parent) : Component(parent)
  {
    // ask graphics module to create model object
  }

  void Model::Initialize()
  {
  }
}