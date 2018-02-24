/**
* \file Engine.hpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Class definition for Engine.
*/

#pragma once

#include "Utilities/StdTypedefs.hpp"
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
    * \brief Engine constructor
    */
    Engine();

    /**
    * \brief Engine destructor
    */
    ~Engine();

    /**
    * \brief Initializes all modules.
    */
    void Initialize();

    // Modules
    UniquePtr<CoreModule> mCoreModule;
    UniquePtr<GraphicsModule> mGraphicsModule;
    UniquePtr<PhysicsModule> mPhysicsModule;
  };

}