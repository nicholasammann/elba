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

namespace Elba
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

    /**
    * \brief Shuts down the engine and all its modules.
    */
    void Shutdown();

    /**
    * \brief Whether or not the engine should be running
    * \return True if Engine should be running, False if Engine is ready to shutdown.
    */
    bool IsRunning() const;

    /**
    * \brief Getter for mCoreModule    
    * \return Pointer to CoreModule
    */
    CoreModule* GetCoreModule();

    /**
    * \brief Getter for mGraphicsModule
    * \return Pointer to GraphicsModule
    */
    GraphicsModule* GetGraphicsModule();

    /**
    * \brief Getter for mPhysicsModule
    * \return Pointer to PhysicsModule
    */
    PhysicsModule* GetPhysicsModule();

  private:
    // Modules
    UniquePtr<CoreModule> mCoreModule;
    UniquePtr<GraphicsModule> mGraphicsModule;
    UniquePtr<PhysicsModule> mPhysicsModule;

    // Running status
    bool mIsRunning;
  };

}