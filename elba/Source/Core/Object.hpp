/**
* \file Object.hpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Class definition for Object.
*/

#pragma once

#include "Core/CoreTypedefs.hpp"

namespace Elba
{
  /**
  * \brief Any possible object in the game.
  */
  class Object
  {
  public:
    /**
    * \brief Constructor
    * \param parent The parent object.
    */
    Object(Object* parent);

    /**
    * \brief Move constructor
    * \param other R-value reference to class type
    */
    Object(Object&& other);

    /**
    * \brief Gets this object's parent.
    * \return The parent of this object.
    */
    Object* Parent() const;

    /**
    * \brief Find a direct child of this object.
    * \param guid Global key of desired object.
    * \return The child object with the given key. nullptr if not found.
    */
    Object* FindChild(const GlobalKey& guid) const;

    /**
    * \brief Creates a new child object.
    * \return The new child object. nullptr if insertion into map of children failed.
    */
    Object* CreateChild();

    /**
    * \brief Getter for object's guid;
    * \return The new child object. nullptr if insertion into map of children failed.
    */
    GlobalKey GetGuid() const;

  private:
    Object* mParent;

    ObjectMap mChildren;

    GlobalKey mGuid;

  };

}