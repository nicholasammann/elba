#pragma once

#include <string>

#include <assimp/Exporter.hpp>

namespace Elba
{

struct Texture
{
  unsigned int mID;
  std::string mType;
  aiString mPath;
};

} // End of Elba namespace
