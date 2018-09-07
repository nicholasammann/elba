/**
* \file ResourceManager.hpp
* \author Nicholas Ammann
* \date 3/29/2018
* \brief Class definition for ResourceManager.
*/

#pragma once

#include "Framework/Resource.hpp"

namespace Elba
{
/**
* \brief Handles loading and unloading of assets.
*/
class ResourceManager
{
public:

  /**
  * \brief Constructor
  */
  ResourceManager();

  /**
  * \brief Destructor
  */
  ~ResourceManager();

  /**
  * \brief Loads the mesh if it hasn't been loaded already, otherwise
  *        returns the already loaded mesh.
  * \param name The name of the mesh to be loaded.
  * \return A pointer to the mesh.
  */
  Resource* LoadMesh(std::string name);

private:

  std::map<std::string, Resource*> mMeshes;

};

} // End of Elba namespace
