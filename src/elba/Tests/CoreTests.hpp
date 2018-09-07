/**
* \file CoreTests.hpp
* \author Nicholas Ammann
* \date 3/10/2018
* \brief Function declarations for test functions for CoreModule.
*/

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

/**
* \brief Runs all tests for CoreModule.
* \param coreModule CoreModule that will be tested.
*/
void RunAllTests(CoreModule* coreModule);

/**
* \brief Creates 10 objects.
* \param coreModule CoreModule that will be tested.
*/
void CreateObjects1(CoreModule* coreModule);

/**
* \brief Creates 100 objects.
* \param coreModule CoreModule that will be tested.
*/
void CreateObjects2(CoreModule* coreModule);

/**
* \brief Creates 1000 objects.
* \param coreModule CoreModule that will be tested.
*/
void CreateObjects3(CoreModule* coreModule);

/**
* \brief Creates 10,000 objects.
* \param coreModule CoreModule that will be tested.
*/
void CreateObjects4(CoreModule* coreModule);

/**
* \brief Creates an input number of objects.
* \param object Parent object of the objects about to be created.
* \param numObjects The number of objects that will be created.
*/
void CreateObjects(Object* object, int numObjects);

} // End of Core namespace
} // End of Test namespace
} // End of Elba namespace
