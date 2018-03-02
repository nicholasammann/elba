/**
* \file Module.hpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Class definition for Module.
*/

#pragma once

namespace Elba
{
  /**
  * \brief Base class for systems that comprise the engine.
  */
  class Module
  {
  public:
    /**
    * \brief Constructor
    */
    Module();

    /**
    * \brief Initialize function that Engine will call on each module.
    */
    virtual void Initialize() = 0;

    /**
    * \brief Update function that Engine will call on each module.
    */
    virtual void Update() = 0;
  };
}