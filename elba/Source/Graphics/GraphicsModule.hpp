/**
* \file GraphicsModule.hpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Class definition for GraphicsModule.
*/

#pragma once

#include "Framework/Module.hpp"

namespace ELBA
{
  /**
  * \brief Module for the graphics system. Manages rendering.
  */
  class GraphicsModule : public Module
  {
  public:
    /**
    * \brief cstor
    */
    GraphicsModule();

    /**
    * \brief Update function called by Engine. Updates graphics.
    */
    void Update() override;

  };

}