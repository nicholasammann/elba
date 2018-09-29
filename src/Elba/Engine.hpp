/**
* \file Engine.hpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Class definition for Engine.
*/

#pragma once

#include <chrono>

#include "Elba/Utilities/StdTypedefs.hpp"
#include "Elba/Core/CoreForwardDeclarations.hpp"
#include "Elba/Graphics/GraphicsForwardDeclarations.hpp"
#include "Elba/Physics/PhysicsForwardDeclarations.hpp"

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
  * \param inEditorMode Is the engine being run inside the editor.
  */
  Engine(bool inEditorMode);

  /**
  * \brief Engine destructor
  */
  ~Engine();

  /**
  * \brief Initializes all modules.
  */
  void Initialize();

  /**
  * \brief Updates all modules.
  */
  void Update();

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

  /**
  * \brief Check if engine is running inside editor.
  * \return True if being run by editor, false otherwise.
  */
  bool InEditor() const;

private:
  // Modules
  UniquePtr<CoreModule> mCoreModule;
  UniquePtr<GraphicsModule> mGraphicsModule;
  UniquePtr<PhysicsModule> mPhysicsModule;

  // Running status
  bool mIsRunning;
  bool mInEditorMode;

  std::chrono::high_resolution_clock::time_point mPreviousTime;
};

} // End of Elba namespace
