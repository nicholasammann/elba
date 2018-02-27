/**
* \file Component.hpp
* \author Nicholas Ammann
* \date 2/27/2018
* \brief Class definition for Component.
*/

#pragma once

#include "Core/CoreForwardDeclarations.hpp"

namespace Elba
{
  /**
  * \brief Component base class.
  */
  class Component
  {
  public:
    /**
    * \brief Constructor
    * \param parent The parent object.
    */
    Component(Object* parent);

    /**
    * \brief Initializes derived class.
    */
    virtual void Initialize() = 0;

  private:
    Object* mParent;

  };
}
