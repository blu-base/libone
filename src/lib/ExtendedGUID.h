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
/** @brief Composite structure class of a GUID object and an unsigned int. */
class ExtendedGUID
{
public:
  /** Default constructor. Initializes the m_guid and m_n variables to zero. */
  ExtendedGUID();
  /** Constructor. Initialize specific GUID and int. */
  ExtendedGUID(const GUID guid, const uint32_t n);

  /** Parses ExtendedGUID's content from RVNGInputStream byte stream. */
  void parse(librevenge::RVNGInputStream *input);

  /** Converts ExtendedGUID object to a string of this format: {{00000000-0000-0000-0000-000000000000},0} */
  std::string to_string() const;

  /** Parse ExtendedGUID object form a string of this format: {{00000000-0000-0000-0000-000000000000},0} */
  void from_string(const std::string str);

  /** Getter for member object m_guid. */
  GUID guid() const;
  /** Getter for member variable m_n */
  uint32_t n() const;

  /** Setter for m_guid. */
  void set_GUID(const GUID new_guid);
  /** Setter for m_n. */
  void set_n(const uint32_t new_n);

  /** @Returns true if m_guid and m_n are identical between both ExtendedGUID objects. */
  bool is_equal(const ExtendedGUID other) const;

  /** Resets this ExtendedGUID to {{00000000-0000-0000-0000-000000000000},0} */
  void zero();

  friend librevenge::RVNGInputStream *operator>>(librevenge::RVNGInputStream *input, ExtendedGUID &obj);

  friend bool operator==(const ExtendedGUID &lhs, const ExtendedGUID &rhs) noexcept;
  friend bool operator!=(const ExtendedGUID &lhs, const ExtendedGUID &rhs) noexcept;

private:
  GUID m_guid;
  uint32_t m_n;
};

}

#endif
