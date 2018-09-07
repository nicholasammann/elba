#include "Elba/Engine.hpp"

int main(int argc, char** argv)
{
  Elba::Engine* engine = new Elba::Engine();

  engine->Initialize();

  while (engine->IsRunning())
  {
    engine->Update();
  }

  engine->Shutdown();

  return 0;
}