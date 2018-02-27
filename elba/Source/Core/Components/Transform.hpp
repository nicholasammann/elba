/**
* \file Transform.hpp
* \author Nicholas Ammann
* \date 2/27/2018
* \brief Class definition for Transform.
*/

#pragma once

#include "Core/Component.hpp"

namespace Elba
{
  /**
  * \brief Interface for communicating with a transform object in the physics module.
  */
  class Transform : public Component
  {
  public:
    /**
    * \brief Constructor
    * \param parent The parent object.
    */
    Transform(Object* parent);

    /**
    * \brief Initializes derived class.
    */
    void Initialize() override;

  private:
    // physics transform
    
  };
}
