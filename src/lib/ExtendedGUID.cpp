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
ExtendedGUID::ExtendedGUID() : m_guid(), m_n(0)
{
}

ExtendedGUID::ExtendedGUID(const GUID guid, const uint32_t n) :
  m_guid(guid), m_n(n)
{}

void ExtendedGUID::parse(librevenge::RVNGInputStream *input)
{
  input >> m_guid;

  m_n = readU32(input, false);
}

std::string ExtendedGUID::to_string() const
{
  std::stringstream stream;
  stream << "{" << m_guid.to_string() << "," << m_n << "}";

  return stream.str();
}

std::string ExtendedGUID::from_string(const std::string str)
{
}

GUID ExtendedGUID::guid() const
{
  return m_guid;
}

uint32_t ExtendedGUID::n() const
{
  return m_n;
}

bool ExtendedGUID::is_equal(const ExtendedGUID other) const
{
  return m_guid == other.m_guid && m_n == other.m_n;
}

void ExtendedGUID::zero()
{
  m_guid.zero();
  m_n = 0;
}

void ExtendedGUID::set_n(uint32_t new_n)
{
  m_n = new_n;
}

void ExtendedGUID::set_GUID(GUID new_guid)
{
  m_guid = new_guid;
}

librevenge::RVNGInputStream *operator>>(librevenge::RVNGInputStream *input, ExtendedGUID &obj)
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

}
