/**
* \file GraphicsModule.hpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Class definition for GraphicsModule.
*/

#pragma once

#include <vector>

#include "Elba/Framework/Module.hpp"

#include "Elba/Graphics/GraphicsFactory.hpp"

namespace Elba
{
class Engine;

/**
* \brief Module for the graphics system. Manages rendering.
*/
class GraphicsModule : public Module
{
public:
  /**
  * \brief Constructor
  * \param engine The engine, which owns all modules.
  */
  GraphicsModule(Engine* engine);

  /**
  * \brief Initialize function called by Engine. Initializes GraphicsModule.
  */
  virtual void Initialize() override = 0;

  /**
  * \brief Update function called by Engine. Updates graphics.
  */
  virtual void Update() override = 0;
  
  /**
  * \brief Window/context agnostic rendering calls.
  */
  virtual void Render() = 0;

  /**
  * \brief Constructs a Mesh and adds it to the graphics module.
  * \param name The name of the fbx file.
  * \return The Mesh that was just created.
  */
  virtual UniquePtr<Mesh> RequestMesh(std::string name) = 0;
};

} // End of Elba namespace
