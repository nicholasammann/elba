/**
* \file StdTypedefs.hpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Typedefs to make standard library look nicer.
*/

#pragma once

#include <memory>
#include <map>
#include <unordered_map>

namespace Elba
{
  // pointers
  template <typename T>
  using UniquePtr = std::unique_ptr<T>;

  //template <typename T, typename... TArgs>
  //constexpr auto NewUnique = &std::make_unique<T, TArgs>;
  
  /**
  * \brief reimplementation of std::make_unique
  * \param args Arguments for constructor of given type
  * \return newly constructed unique ptr
  */
  template<typename T, typename... Args>
  UniquePtr<T> NewUnique(Args&&... args)
  {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
  }


  // containers
  template <typename T>
  using Vector = std::vector<T>;

  template <typename Key, typename T>
  using Map = std::map<Key, T>;

  template <typename Key, typename T>
  using UnorderedMap = std::unordered_map<Key, T>;

}