/**
* \file Model.cpp
* \author Nicholas Ammann
* \date 2/27/2018
* \brief Member function definitions for Model.
*/

#include "Elba/Engine.hpp"
#include "Elba/Core/Object.hpp"
#include "Elba/Core/CoreModule.hpp"
#include "Elba/Core/Components/Model.hpp"
#include "Elba/Graphics/GraphicsModule.hpp"

namespace Elba
{
Model::Model(Object* parent) : Component(parent)
{
  // ask graphics module to create model object
  CoreModule* core = parent->GetCoreModule();
  Engine* engine = core->GetEngine();
  GraphicsModule* graphics = engine->GetGraphicsModule();
  GraphicsFactory* factory = graphics->GetFactory();

  mMesh = factory->CreateMesh();
}

void Model::Initialize()
{

}

} // End of Elba namespace
