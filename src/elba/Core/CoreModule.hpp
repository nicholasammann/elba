/**
* \file CoreModule.hpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Class definition for CoreModule.
*/

#pragma once

#include "Utilities/StdTypedefs.hpp"

#include "Framework/Module.hpp"

#include "Core/CoreForwardDeclarations.hpp"
#include "Core/Object.hpp"


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
    Object* GetGameWorld();

  private:

    UniquePtr<Object> mGameWorld;

  };

}