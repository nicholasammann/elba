#include "Elba/Core/Object.hpp"
#include "Elba/Core/Components/Rotate.hpp"
#include "Elba/Core/Components/Transform.hpp"

namespace Elba
{

Rotate::Rotate(Object* object)
  : Component(object)
  , mTransform(nullptr)
  , mTimeSince(0.0f)
  , mMoveSpeed(0.0f)
  , mRotateSpeed(0.0f)
{
}

void Rotate::Initialize()
{
  mTransform = GetParent()->GetComponent<Transform>();
  mOrigPos = mTransform->GetWorldTranslation();
}

void Rotate::Update(double dt)
{
  mTimeSince += static_cast<float>(dt);

  glm::quat rot = mTransform->GetWorldRotation();
  glm::quat change(glm::vec3(0.0f, mRotateSpeed * static_cast<float>(.003), 0.0f));
  rot *= change;
  mTransform->SetWorldRotation(rot);

  float move = sin(mMoveSpeed * mTimeSince);
  glm::vec3 pos = mOrigPos;
  pos.x += 3.0f * move;
  mTransform->SetWorldTranslation(pos);
}

void Rotate::SetRotateSpeed(float speed)
{
  mRotateSpeed = speed;
}

void Rotate::SetMoveSpeed(float speed)
{
  mMoveSpeed = speed;
}

} // End of Elba namespace

