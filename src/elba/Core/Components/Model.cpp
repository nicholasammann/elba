/**
* \file Model.cpp
* \author Nicholas Ammann
* \date 2/27/2018
* \brief Member function definitions for Model.
*/

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

#include "Elba/Engine.hpp"
#include "Elba/Core/Object.hpp"
#include "Elba/Core/CoreModule.hpp"
#include "Elba/Core/Components/Model.hpp"
#include "Elba/Graphics/GraphicsModule.hpp"

namespace Elba
{
Model::Model(Object* parent)
: Component(parent)
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
  mMesh->Initialize();

  graphicsModule->RegisterForDraw(GetGuid(), 
    [this](const DrawEvent& drawEvent)
    {
      Transform* transform = this->GetParent()->GetComponent<Transform>();
      
      glm::mat4 scale = glm::scale(transform->GetWorldScale());
      glm::mat4 rotate = glm::toMat4(transform->GetWorldRotation());
      glm::mat4 translate = glm::translate(transform->GetWorldTranslation());

      glm::mat4 modelMat = translate * rotate * scale;

      mMesh->Draw(drawEvent.proj, drawEvent.view, modelMat);
    }
  );
}

void Model::LoadShader(std::string name)
{
  mMesh->LoadShader(name);
}

Mesh* Model::GetMesh() const
{
  return mMesh.get();
}

} // End of Elba namespace
