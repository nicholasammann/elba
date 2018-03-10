/**
* \file PhysicsModule.hpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Class definition for PhysicsModule.
*/

#pragma once

#include "Framework/Module.hpp"

#include "Physics/PhysicsForwardDeclarations.hpp"
#include "Physics/PhysicsFactory.hpp"

#include "Utilities/StdTypedefs.hpp"

namespace Elba
{
  class Engine;

  /**
  * \brief Module for the physics system. Manages physics for game objects.
  * \param Pointer to engine, which owns all modules.
  */
  class PhysicsModule : public Module
  {
  public:
    /**
    * \brief Constructor
    */
    PhysicsModule(Engine* engine);

    /**
    * \brief Initialize function called by Engine. Initializes PhysicsModule.
    */
    void Initialize() override;

    /**
    * \brief Update function called by Engine. Updates physics.
    */
    void Update() override;

    /**
    * \brief Getter for the PhysicsFactory.
    */
    PhysicsFactory* GetFactory() const;

  private:
    UniquePtr<PhysicsFactory> mFactory;

  };

}