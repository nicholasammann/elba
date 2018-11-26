#include "Elba/Core/Object.hpp"
#include "Elba/Core/Components/Rotate.hpp"
#include "Elba/Core/Components/Transform.hpp"

namespace Elba
{

Rotate::Rotate(Object* object)
  : Component(object)
  , mTransform(nullptr)
{
}

void Rotate::Initialize()
{
  mTransform = GetParent()->GetComponent<Transform>();
}

void Rotate::Update(double dt)
{
  glm::quat rot = mTransform->GetWorldRotation();

  glm::quat change(glm::vec3(0.0f, static_cast<float>(.08), 0.0f));

  rot *= change;

  mTransform->SetWorldRotation(rot);
}

} // End of Elba namespace

