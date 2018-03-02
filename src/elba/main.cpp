/**
* \file main.cpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Main function. Constructs Engine.
*/

#include "Tests/CoreTests.hpp"

#include "Engine.hpp"
#include "Core/CoreModule.hpp"

/**
* \brief main function
*/
int main(int argc, char** argv)
{
  Elba::Engine* elba = new Elba::Engine();

  elba->Initialize();

  Elba::CoreModule* coreModule = elba->GetCoreModule();

  Elba::Test::CoreTest1(coreModule);

  return 0;
}