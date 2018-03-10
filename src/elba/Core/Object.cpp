/**
* \file Object.cpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Member function definitions for Object.
*/

#include "Core/Object.hpp"
#include "Core/Component.hpp"

namespace Elba
{
  Object::Object(Object* parent)
    : mParent(parent)
    , mChildren()
    , mGuid()
  {
    mCoreModule = parent ? parent->GetCoreModule() : nullptr;
  }

  Object* Object::Parent() const
  {
    return mParent;
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

  Component* Object::FindComponent(const GlobalKey& guid) const
  {
    auto it = mComponents.find(guid);

    if (it != mComponents.end())
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
}