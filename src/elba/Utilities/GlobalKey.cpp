/**
* \file GlobalKey.cpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Member function definitions for GUID.
*/

#include "Utilities/GlobalKey.hpp"

namespace Elba
{
GlobalKey::GlobalKey()
{
  HRESULT error;

  do
  {
    // generates the guid
    error = CoCreateGuid(&mGuid);

    // check if successfully created
  } while (error != S_OK);
}

GUID GlobalKey::GetGuid() const
{
  return mGuid;
}

std::string GlobalKey::ToStdString() const
{
  std::string result;

  result += std::to_string(mGuid.Data1) + "-";
  result += std::to_string(mGuid.Data2) + "-";
  result += std::to_string(mGuid.Data3) + "-";
  result += std::string(mGuid.Data4, mGuid.Data4 + sizeof(mGuid.Data4) / sizeof(mGuid.Data4[0]));

  return result;
}

bool GlobalKey::operator<(const GlobalKey& rhs) const
{
  GUID rGuid = rhs.GetGuid();

  return memcmp(&mGuid, &rGuid, sizeof(rGuid)) < 0;
}

} // End of Elba namespace
