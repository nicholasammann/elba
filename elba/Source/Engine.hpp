/**
* \file Engine.hpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Class definition for Engine.
*/

#pragma once

#include "Core/CoreForwardDeclarations.hpp"
#include "Graphics/GraphicsForwardDeclarations.hpp"
#include "Physics/PhysicsForwardDeclarations.hpp"

namespace ELBA
{
  /**
  * \brief Handles all the modules that comprise the game engine.
  */
  class Engine
  {
  public:
    /**
    * \brief cstor
    */
    Engine();

    // Modules
    CoreModule* mCoreModule;
    GraphicsModule* mGraphicsModule;
    PhysicsModule* mPhysicsModule;
  };

}