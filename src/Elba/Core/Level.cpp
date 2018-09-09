#include "Elba/Core/Level.hpp"

namespace Elba
{

Level::Level()
: Object(nullptr)
, mName("NewLevel")
{
}

void Level::LoadLevel(std::string name)
{

}

void Level::SaveLevelAs(std::string name)
{

}

void Level::SaveLevel()
{
  SaveLevelAs(mName);
}

}

