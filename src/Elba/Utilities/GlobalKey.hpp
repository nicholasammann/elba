/**
* \file GlobalKey.hpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Class definition for GUID.
*/

#pragma once

#include <string>
#include <objbase.h>


namespace Elba
{
/**
* \brief Wrapper around CoCreateGuid.
*/
class GlobalKey
{
public:
  /**
  * \brief Constructor
  */
  GlobalKey();

  /**
  * \brief Getter for underlying GUID data.
  * \return Underlying GUID struct.
  */
  GUID GetGuid() const;

  /**
  * \brief Converts the data to string.
  * \return Guid in string form.
  */
  std::string ToStdString() const;


  /**
  * \brief Getter for underlying GUID data.
  * \param rhs GlobalKey we are comparing against.
  * \return True if this key is less than the key passed in.
  */
  bool operator<(const GlobalKey& rhs) const;

private:
  GUID mGuid;

};
} // End of Elba namespace
