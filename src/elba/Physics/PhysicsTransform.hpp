/**
* \file PhysicsTransform.hpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Class definition for PhysicsTransform.
*/

#pragma once

#include "Framework/Module.hpp"

namespace Elba
{
  /**
  * \brief Represents position, rotation and scale of an object in physics system.
  */
  class PhysicsTransform
  {
  public:
    /**
    * \brief Constructor
    */
    PhysicsTransform();

    /**
    * \brief Update function called by PhysicsModule. Updates physics.
    */
    void Update();

  private:
    

  };

}