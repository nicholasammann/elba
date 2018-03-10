#pragma once

#include "Core/CoreForwardDeclarations.hpp"

#include "Core/Object.hpp"
#include "Core/CoreModule.hpp"

namespace Elba
{
  namespace Test
  {
    namespace Core
    {
      void RunAllTests(CoreModule* coreModule);

      void CreateObjects1(CoreModule* coreModule);
      void CreateObjects2(CoreModule* coreModule);
      void CreateObjects3(CoreModule* coreModule);
      void CreateObjects4(CoreModule* coreModule);

      // helper functions
      void CreateObjects(Object* object, int numObjects);
    }
  }
}