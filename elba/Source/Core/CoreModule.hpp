/**
* \file CoreModule.hpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Class definition for CoreModule.
*/

#pragma once

#include "Framework/Module.hpp"

namespace ELBA
{
  /**
  * \brief Module for the core of the engine. Manages objects.
  */
  class CoreModule : public Module
  {
  public:
    /**
    * \brief constructor
    */
    CoreModule();

    /**
    * \brief Update function called by Engine. Updates all game objects.
    */
    void Update() override;

  };

}