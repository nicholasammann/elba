/**
* \file Model.hpp
* \author Nicholas Ammann
* \date 2/27/2018
* \brief Class definition for Model.
*/

#pragma once

#include "Core/Component.hpp"

namespace Elba
{
  /**
  * \brief Interface for communicating with a model object in the graphics module. 
  The graphics related data should all be contained in the graphics module.
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

  private:

    // graphics model

  };
}
