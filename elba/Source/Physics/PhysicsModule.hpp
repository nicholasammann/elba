/**
* \file PhysicsModule.hpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Class definition for PhysicsModule.
*/

#pragma once

#include "Framework/Module.hpp"

namespace ELBA
{
  /**
  * \brief Module for the physics system. Manages physics for game objects.
  */
  class PhysicsModule : public Module
  {
  public:
    /**
    * \brief cstor
    */
    PhysicsModule();

    /**
    * \brief Update function called by Engine. Updates physics.
    */
    void Update() override;

  };

}