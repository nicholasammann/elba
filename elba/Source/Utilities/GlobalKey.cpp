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