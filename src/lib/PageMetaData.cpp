/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "PageMetaData.h"

namespace libone
{

PageMetaData::PageMetaData(const libone::RVNGInputStreamPtr_t &input, struct object_header _header) : Object(input, _header)
{
//    Object(_header);
  (void) input;

}

}
