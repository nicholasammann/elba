#include <iostream>

#include "Utilities/GlobalKey.hpp"

#include "Tests/CoreTests.hpp"

namespace Elba
{
  namespace Test
  {
    void CoreTest1(CoreModule* core)
    {
      Object* world = core->GetGameWorld();

      CreateObjects(world, 10);
    }

    void CoreTest2(CoreModule* core)
    {
      Object* world = core->GetGameWorld();

      CreateObjects(world, 100);
    }

    void CoreTest3(CoreModule* core)
    {
      Object* world = core->GetGameWorld();

      CreateObjects(world, 1000);
    }

    void CoreTest4(CoreModule* core)
    {
      Object* world = core->GetGameWorld();

      CreateObjects(world, 10000);
    }

    void CreateObjects(Object* object, int numObjects)
    {
      for (int i = 0; i < numObjects; i++)
      {
        Object* obj = object->CreateChild();

        GlobalKey guid = obj->GetGuid();

        std::string guidStr = guid.ToStdString();

        std::cout << "Object " << i << " created.  ID: " << guidStr << std::endl;
      }
    }
  }
}