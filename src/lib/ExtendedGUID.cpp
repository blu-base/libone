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
#include <iostream>
#include <iomanip>
#include <sstream>
#include <libone/libone.h>

#include "ExtendedGUID.h"

#include "libone_utils.h"

namespace libone
{
// {{FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF},4294967295}
enum { MaxStringEGUIDLength = 51};
// FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF,0
enum { MinStringEGUIDLength = 34};

ExtendedGUID::ExtendedGUID() : m_guid(), m_n(0)
{
}

ExtendedGUID::ExtendedGUID(const GUID guid, const uint32_t n) :
  m_guid(guid), m_n(n)
{
}

ExtendedGUID::ExtendedGUID(const uint32_t data1, const uint16_t data2, const uint16_t data3,
                           const uint16_t data4_1, const uint16_t data4_2,
                           const uint16_t data4_3, const uint16_t data4_4,
                           const uint32_t n) :
  m_guid(GUID(data1, data2, data3, data4_1, data4_2, data4_3, data4_4)),
  m_n(n) {}


std::string ExtendedGUID::to_string() const
{
  std::stringstream stream;
  stream << "{" << m_guid.to_string() << "," << m_n << "}";

  return stream.str();
}

void ExtendedGUID::from_string(const std::string str)
{
  if (str.size() < MinStringEGUIDLength -1)
  {
    (void) str;
  }

  if (
    (str.front() == '{' && str.size() > MaxStringEGUIDLength - 1)
    || (str.front() != '{' && str.at(9) == '-' && str.size() > MaxStringEGUIDLength - 3))
  {
    (void) str;
  }

  // separator position
  auto s_pos = str.find(',');

  if (s_pos == std::string::npos)
  {
    ONE_DEBUG_MSG(("Parsing of ExtendedGUID failed. No comma separator"));
    (void) str;
  }

  size_t i{0};
  str.at(i) == '{' ? i++ : 0;

  m_guid.from_string(str.substr(i, s_pos-i-1));

  // remaining size
  size_t n_size = str.size() - s_pos -1 ;

  str.at(str.size() -1) == '}' ? n_size-- : 0;

  m_n = strtol(str.substr(s_pos + 1, n_size).c_str(), NULL, 16);

  (void) str;


}

uint32_t ExtendedGUID::n() const
{
  return m_n;
}

GUID ExtendedGUID::guid() const
{
  return m_guid;
}


void ExtendedGUID::set_n(uint32_t new_n)
{
  m_n = new_n;
}

void ExtendedGUID::set_GUID(GUID new_guid)
{
  m_guid = new_guid;
}


void ExtendedGUID::zeroing()
{
  m_guid = GUID();
  m_n = 0;
}

librevenge::RVNGInputStream &operator>>(librevenge::RVNGInputStream *input, ExtendedGUID &obj)
{
  obj.parse(input);
  return input;
}

bool operator==(const ExtendedGUID &lhs, const ExtendedGUID &rhs) noexcept
{
  return lhs.is_equal(rhs);
}

bool operator!=(const ExtendedGUID &lhs, const ExtendedGUID &rhs) noexcept
{
  return ! lhs.is_equal(rhs);
}

void ExtendedGUID::parse(librevenge::RVNGInputStream *input)
{
  input >> m_guid;

  m_n = readU32(input, false);
}

bool ExtendedGUID::is_equal(const ExtendedGUID &other) const
{
  if ((m_guid == other.m_guid) && (m_n == other.m_n))
  {
    return true;
  }
  return false;
}
} // namespace libone
