/**
* \file PhysicsFactory.hpp
* \author Nicholas Ammann
* \date 2/27/2018
* \brief Class definition for PhysicsFactory.
*/

#pragma once

namespace Elba
{
  /**
  * \brief Handles creation of objects in PhysicsModule.
  */
  class PhysicsFactory
  {
  public:
    /**
    * \brief Constructor
    */
    PhysicsFactory();

    /**
    * \brief Constructs a transform and adds it to the physics system.
    */
    void CreatePhysicsTransform();

  };

}