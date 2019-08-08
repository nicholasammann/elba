/**
* \file PhysicsModule.hpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Class definition for PhysicsModule.
*/

#pragma once

#include <vector>

#include "Elba/Framework/Module.hpp"

#include "Elba/Physics/PhysicsForwardDeclarations.hpp"
#include "Elba/Physics/PhysicsFactory.hpp"

#include "Elba/Utilities/StdTypedefs.hpp"

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
  void Update(double dt) override;

  /**
  * \brief Getter for the PhysicsFactory.
  * \return The PhysicsFactory owned by this Module.
  */
  PhysicsFactory* GetFactory() const;

private:
  UniquePtr<PhysicsFactory> mFactory;
  friend PhysicsFactory;

  std::vector<PhysicsTransform*> mPhysicsTransforms;

};

} // End of Elba namespace
