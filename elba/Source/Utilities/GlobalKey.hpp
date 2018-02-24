/**
* \file GlobalKey.hpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Class definition for GUID.
*/

#pragma once

#include <objbase.h>


namespace ELBA
{
  /**
  * \brief Wrapper around CoCreateGuid.
  */
  class GlobalKey
  {
  public:
    /**
    * \brief cstor
    */
    GlobalKey();

  private:
    GUID mGuid;

  };
}