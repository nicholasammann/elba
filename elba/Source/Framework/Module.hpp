/**
* \file Module.hpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Class definition for Module.
*/

#pragma once

namespace ELBA
{
  /**
  * \brief Base class for systems that comprise the engine.
  */
  class Module
  {
  public:
    /**
    * \brief cstor
    */
    Module();

    /**
    * \brief Update function that Engine will call on each module.
    */
    virtual void Update() = 0;
  };
}