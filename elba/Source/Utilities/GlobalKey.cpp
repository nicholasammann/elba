/**
* \file GlobalKey.cpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Member function definitions for GUID.
*/

#include "Utilities/GlobalKey.hpp"

namespace ELBA
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
}