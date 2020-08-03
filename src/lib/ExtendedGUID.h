/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_EXTENDEDGUID_H
#define INCLUDED_LIBONE_EXTENDEDGUID_H

#include "GUID.h"


namespace libone
{
class ExtendedGUID
{
public:
  ExtendedGUID();
  ExtendedGUID(const GUID guid, const uint32_t n);
  ExtendedGUID(const uint32_t data1, const uint16_t data2, const uint16_t data3,
               const uint16_t data4_1, const uint16_t data4_2,
               const uint16_t data4_3, const uint16_t data4_4,
               const uint32_t n);

  std::string to_string() const;
  void from_string(const std::string str);

  uint32_t n() const;
  GUID guid() const;

  void set_GUID(const GUID new_guid);
  void set_n(const uint32_t new_n);

  void zeroing();


  friend librevenge::RVNGInputStream &operator>>(librevenge::RVNGInputStream *input, ExtendedGUID &obj);

  friend bool operator==(const ExtendedGUID &lhs, const ExtendedGUID &rhs) noexcept;
  friend bool operator!=(const ExtendedGUID &lhs, const ExtendedGUID &rhs) noexcept;

private:
  void parse(librevenge::RVNGInputStream *input);
  bool is_equal(const ExtendedGUID &other) const;

  GUID m_guid;
  uint32_t m_n;

};

}

#endif
