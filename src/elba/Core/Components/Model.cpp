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
Model::Model(Object* parent)
: Component(parent)
, mMesh()
{
}

void Model::Initialize()
{

}

void Model::LoadMesh(std::string name)
{
  CoreModule* core = GetParent()->GetCoreModule();
  Engine* engine = core->GetEngine();
  GraphicsModule* graphicsModule = engine->GetGraphicsModule();

  // get mesh from graphics factory
  mMesh = graphicsModule->RequestMesh(name);
}

} // End of Elba namespace
