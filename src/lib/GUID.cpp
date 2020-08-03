/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */


#include <cstddef>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <libone/libone.h>

#include "libone_utils.h"

#include "GUID.h"

namespace libone
{

enum { MaxStringGUIDLength = 38};
enum { MinStringGUIDLength = 32};

GUID::GUID() :
  Data1(0), Data2(0), Data3(0), Data4{0,0,0,0}
{
}

GUID::GUID(const uint32_t data1, const uint16_t data2, const uint16_t data3,
           const uint16_t data4_1, const uint16_t data4_2,
           const uint16_t data4_3, const uint16_t data4_4) :
  Data1(data1), Data2(data2), Data3(data3), Data4{data4_1, data4_2, data4_3, data4_4}
{
}

void GUID::parse(librevenge::RVNGInputStream *input)
{
  Data1 = readU32(input, false);
  Data2 = readU16(input, false);
  Data3 = readU16(input, false);
  for (int i=0; i<4; i++)
    Data4[i] = readU16(input, true);
}

std::string GUID::to_string()
{
  std::stringstream stream;
  stream << "{" <<  int_to_hex(Data1) << Data1 << "-" << int_to_hex(Data2) << "-" << int_to_hex(Data3) << "-" << int_to_hex(Data4[0]) << "-";

  for (int i=1; i<4; i++)
    stream << int_to_hex(Data4[i]);

  stream << "}";

  return stream.str();
}

bool GUID::is_equal(const GUID other) const
{
  if ((Data1 == other.Data1) &&
      (Data2 == other.Data2) &&
      (Data3 == other.Data3))
  {
    for (int i=0; i<4; i++)
    {
      if (Data4[i] != other.Data4[i])
        return false;
    }
    return true;
  }
  return false;
}

// This is used for FileDataStores. The GUID is given as a string in the file
void GUID::from_string(std::string const str)
{
  ONE_DEBUG_MSG(("\n"));

  if (str.size() < MinStringGUIDLength -1
      || (str.front() == '{' && str.size() > MaxStringGUIDLength - 1)
      || (str.front() != '{' && str.at(8) == '-' && str.size() > MaxStringGUIDLength - 3))
  {
    (void) str;
  }

  size_t i{0};
  str.at(i) == '{' ? i++ : 0;
  Data1 = strtol(str.substr(i, 8).c_str(), NULL, 16);
  i += 8;
  str.at(i) == '-' ? i++ : 0;
  Data2 = strtol(str.substr(i, 4).c_str(), NULL, 16);
  i += 4;
  str.at(i) == '-' ? i++ : 0;
  Data3 = strtol(str.substr(i, 4).c_str(), NULL, 16);
  i += 4;
  str.at(i) == '-' ? i++ : 0;
  Data4[0] = strtol(str.substr(i, 4).c_str(), NULL, 16);
  i += 4;
  str.at(i) == '-' ? i++ : 0;
  Data4[1] = strtol(str.substr(i, 4).c_str(), NULL, 16);
  i+= 4;
  Data4[2] = strtol(str.substr(i, 4).c_str(), NULL, 16);
  i+= 4;
  Data4[3] = strtol(str.substr(i, 4).c_str(), NULL, 16);
  i+= 4;


  ONE_DEBUG_MSG((" from string, dat good?\n"));

  (void) str;
}


librevenge::RVNGInputStream &operator>>(librevenge::RVNGInputStream &is, GUID &obj)
{
  obj.parse(&is);
  return is;
}

bool operator==(const GUID &lhs, const GUID &rhs) noexcept
{
  return lhs.is_equal(rhs);
}
bool operator!=(const GUID &lhs, const GUID &rhs) noexcept
{
  return !(lhs == rhs);
}

} // namespace libone
