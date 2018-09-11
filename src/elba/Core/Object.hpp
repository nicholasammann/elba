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

#include "Elba/Core/Components/Transform.hpp"
#include "Elba/Core/Components/Model.hpp"

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

  /**
  * \brief Creates component of given type and adds it to the object.
  */
  template <typename T, typename... Args>
  T* AddComponent(Args&&... args);

  /**
  * \brief Returns first pointer of given component type
  */
  template <typename T>
  T* GetComponent() const;

private:
  // so CoreModule can set the pointer to itself on the root object
  friend class CoreModule;
  CoreModule* mCoreModule;

  Object* mParent;

  ObjectMap mChildren;

  ComponentMap mComponents;

  GlobalKey mGuid;

};

template <typename T, typename... Args>
T* Object::AddComponent(Args&&... args)
{
  ComponentMap::iterator inserted = mComponents.emplace(std::type_index(typeid(T)), NewUnique<T>(this, std::forward<Args>(args)...));
  return static_cast<T*>(inserted->second.get());
}

template <typename T>
T* Object::GetComponent() const
{
  auto it = mComponents.find(std::type_index(typeid(T)));

  if (it != mComponents.end())
  {
    return static_cast<T*>(it->second.get());
  }

  return nullptr;
}

} // End of Elba namespace
