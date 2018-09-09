/**
* \file Object.hpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Class definition for Object.
*/

#pragma once

#include "Elba/Core/CoreTypedefs.hpp"
#include "Elba/Utilities/GlobalKey.hpp"
#include "Elba/Core/Component.hpp"

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
  * \brief Gets this object's parent.
  * \return The parent of this object.
  */
  Object* GetParent() const;

  /**
  * \brief Find a direct child of this object.
  * \param guid Global key of desired object.
  * \return The child object with the given key. nullptr if not found.
  */
  Object* FindChild(const GlobalKey& guid) const;

  /**
  * \brief Find a component on this object.
  * \param guid Global key of desired component.
  * \return The component with the given key. nullptr if not found.
  */
  Component* FindComponent(const GlobalKey& guid) const;

  /**
  * \brief Creates a new child object.
  * \return The new child object. nullptr if insertion into map of children failed.
  */
  Object* CreateChild();

  /**
  * \brief Getter for object's guid;
  * \return The guid of the object.
  */
  GlobalKey GetGuid() const;

  /**
  * \brief Getter for the core module;
  * \return The core module.
  */
  CoreModule* GetCoreModule() const;

  /**
  * \brief Updates all child objects and components on this object.
  */
  virtual void Update();

private:
  // so CoreModule can set the pointer to itself on the root object
  friend class CoreModule;
  CoreModule* mCoreModule;

  Object* mParent;

  ObjectMap mChildren;

  ComponentMap mComponents;

  GlobalKey mGuid;

};

} // End of Elba namespace
