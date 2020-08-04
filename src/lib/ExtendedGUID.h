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

  void parse(librevenge::RVNGInputStream *input);

  std::string to_string() const;
  void from_string(const std::string str);

  GUID guid() const;
  uint32_t n() const;
  void set_GUID(const GUID new_guid);
  void set_n(const uint32_t new_n);

  bool is_equal(ExtendedGUID other);

  void zero();

  friend librevenge::RVNGInputStream *operator>>(librevenge::RVNGInputStream *input, ExtendedGUID &obj);

  friend bool operator==(const ExtendedGUID &lhs, const ExtendedGUID &rhs) noexcept;
  friend bool operator!=(const ExtendedGUID &lhs, const ExtendedGUID &rhs) noexcept;

private:
  GUID guid;
  uint32_t n;
};

}

#endif
