/**
* \file GraphicsModule.hpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Class definition for GraphicsModule.
*/

#pragma once

#include <vector>
#include <functional>

#include "Elba/Framework/Module.hpp"

#include "Elba/Graphics/GraphicsFactory.hpp"

namespace Elba
{
class Engine;

struct DrawEvent
{
  glm::mat4 proj;
  glm::mat4 view;
};
typedef std::function<void(const DrawEvent&)> DrawCallback;

struct ResizeEvent
{
  glm::vec2 oldSize;
  glm::vec2 newSize;
};
typedef std::function<void(const ResizeEvent&)> ResizeCallback;

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
  virtual void Update(double dt) override = 0;

  /**
  * \brief Window/context agnostic rendering calls.
  */
  virtual void Render(int screenWidth, int screenHeight) = 0;

  /**
  * \brief Constructs a Mesh and adds it to the graphics module.
  * \param name The name of the fbx file.
  * \return The Mesh that was just created.
  */
  virtual UniquePtr<Mesh> RequestMesh(std::string name) = 0;

  void RegisterForDraw(GlobalKey key, DrawCallback callback);
  bool DeregisterForDraw(GlobalKey key);

  void RegisterForResize(GlobalKey key, ResizeCallback callback);
  bool DeregisterForResize(GlobalKey key);

  void OnResize(const ResizeEvent& event);

protected:
  std::vector<std::pair<GlobalKey, DrawCallback> > mDrawCallbacks;
  std::vector<std::pair<GlobalKey, ResizeCallback> > mResizeCallbacks;

};

} // End of Elba namespace
