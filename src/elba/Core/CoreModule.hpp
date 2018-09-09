/**
* \file CoreModule.hpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Class definition for CoreModule.
*/

#pragma once

#include "Elba/Utilities/StdTypedefs.hpp"

#include "Elba/Framework/Module.hpp"

#include "Elba/Core/CoreForwardDeclarations.hpp"
#include "Elba/Core/Level.hpp"


namespace Elba
{
class Engine;

/**
* \brief Module for the core of the engine. Manages objects.
*/
class CoreModule : public Module
{
public:
  /**
  * \brief Constructor
  * \param engine Pointer to engine, which owns all modules.
  */
  CoreModule(Engine* engine);

  /**
  * \brief Initialize function called by Engine. Initializes CoreModule.
  */
  void Initialize() override;

  /**
  * \brief Update function called by Engine. Updates all game objects.
  */
  void Update() override;

  /**
  * \brief Getter for game world object.
  * \return Game world object.
  */
  Level* GetGameLevel();

private:

  UniquePtr<Level> mGameLevel;
};

} // End of Elba namespace
