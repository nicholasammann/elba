#include <filesystem>

#include "Elba/Utilities/Utils.hpp"

namespace Elba
{

namespace Utils
{

std::string GetAssetsDirectory()
{
  return std::experimental::filesystem::current_path().string() + "/../../../Assets/";
}

} // End of Utils namespace

} // End of Elba namespace

