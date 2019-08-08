/**
* \file ResourceManager.hpp
* \author Nicholas Ammann
* \date 3/29/2018
* \brief Class definition for Resource.
*/

#pragma once

#include <map>

namespace Elba
{
/**
* \brief Base class for resources to inherit from.
*/
class Resource
{
public:

  /**
  * \brief Constructor
  */
  Resource(std::string identifier);

  /**
  * \brief Destructor
  */
  virtual ~Resource();

private:

  std::string mIdentifier;

};

} // End of Elba namespace
