/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_STRINGINSTORAGEBUFFER_H
#define INCLUDED_LIBONE_STRINGINSTORAGEBUFFER_H

#include <string>
#include <librevenge-stream/librevenge-stream.h>
#include <vector>

namespace libone {

class StringInStorageBuffer {
  public:
    void parse(librevenge::RVNGInputStream *input);
    uint32_t length = 0;
    std::string to_string();

  private:
    std::string chars = std::string();
};

}

#endif
