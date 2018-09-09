#pragma once

#include "Elba/Core/Object.hpp"

namespace Elba
{

class Level : public Object
{
public:
  Level();

  void LoadLevel(std::string name);

  void SaveLevelAs(std::string name);
  void SaveLevel();

private:
  std::string mName;

};

}
