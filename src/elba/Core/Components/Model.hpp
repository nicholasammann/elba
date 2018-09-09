/**
* \file Model.hpp
* \author Nicholas Ammann
* \date 2/27/2018
* \brief Class definition for Model.
*/

#pragma once

#include "Elba/Core/Component.hpp"
#include "Elba/Graphics/Mesh.hpp"

namespace Elba
{
/**
* \brief Interface for communicating with a mesh.
*/
class Model : public Component
{
public:
  /**
  * \brief Constructor
  * \param parent The parent object.
  */
  Model(Object* parent);

  /**
  * \brief Initializes derived class.
  */
  void Initialize() override;

  /**
  * \brief Loads a new mesh for this model component.
  * \param name The name of the mesh (fbx file).
  */
  void LoadMesh(std::string name);

private:
  // graphics mesh
  UniquePtr<Mesh> mMesh;

};

} // End of Elba namespace
