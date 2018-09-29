#pragma once

#include "Elba/Core/Component.hpp"

namespace Elba
{

class Transform;

class Rotate : public Component
{
public:
  Rotate(Object* object);

  void Initialize() final;

  void Update(double dt) final;

private:

  Transform* mTransform;

};

} // End of Elba namespace

