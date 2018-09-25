/**
* \file Object.cpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Member function definitions for Object.
*/

#include "Elba/Core/Object.hpp"
#include "Elba/Core/Component.hpp"

namespace Elba
{
Object::Object(Object* parent)
  : mParent(parent)
  , mChildren()
  , mGuid()
{
  mCoreModule = parent ? parent->GetCoreModule() : nullptr;
}

Object* Object::GetParent() const
{
  return mParent;
}

ObjectMap const& Object::GetChildren() const
{
  return mChildren;
}

Object* Object::FindChild(const GlobalKey& guid) const
{
  auto it = mChildren.find(guid);

  if (it != mChildren.end())
  {
    return it->second.get();
  }

  return nullptr;
}

Object* Object::CreateChild()
{
  UniquePtr<Object> child = NewUnique<Object>(this);

  auto result = mChildren.emplace(child->mGuid, std::move(child));

  // check if insertion was successful
  if (result.second)
  {
    // return raw ptr to inserted Object
    return result.first->second.get();
  }

  // insertion failed
  return nullptr;
}

GlobalKey Object::GetGuid() const
{
  return mGuid;
}

CoreModule* Object::GetCoreModule() const
{
  return mCoreModule;
}

void Object::Update()
{
  // Update components on this object
  for (std::pair<const std::type_index, UniquePtr<Component> >& component : mComponents)
  {
    component.second->Update();
  }

  // Update child objects
  for (std::pair<const GlobalKey, UniquePtr<Object> >& child : mChildren)
  {
    child.second->Update();
  }
}

} // End of Elba namespace
