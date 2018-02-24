#pragma once

#include "Core/CoreForwardDeclarations.hpp"

#include "Core/Object.hpp"
#include "Core/CoreModule.hpp"

namespace Elba
{
  namespace Test
  {
    void CoreTest1(CoreModule* core);
    void CoreTest2(CoreModule* core);
    void CoreTest3(CoreModule* core);
    void CoreTest4(CoreModule* core);

    void CreateObjects(Object* object, int numObjects);
  }
}