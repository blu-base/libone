/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_OBJECT_H
#define INCLUDED_LIBONE_OBJECT_H

#include <string>
#include <librevenge-stream/librevenge-stream.h>

#include "ExtendedGUID.h"
#include "FileNodeList.h"
#include "GUID.h"
#include "JCID.h"

namespace libone {

class Object {
  public:
    void parse(librevenge::RVNGInputStream *input, FileChunkReference ref);
    void parse_3(librevenge::RVNGInputStream *input);
    bool get_read_only();
    void set_read_only(bool new_);
    ExtendedGUID get_guid();
    std::string to_string();
    unsigned int ref_count = 0;
    void parse_list(librevenge::RVNGInputStream *input, FileChunkReference ref);

  private:
    bool read_only = false;
    ExtendedGUID guid = ExtendedGUID();
    JCID jcid = JCID(0);
    uint16_t fHasOidReferences = 0;
    uint16_t fHasOsidReferences = 0;
    std::vector<ExtendedGUID> object_refs = std::vector<ExtendedGUID>();
    std::vector<ExtendedGUID> context_refs = std::vector<ExtendedGUID>();
    std::vector<ExtendedGUID> object_spaces_refs = std::vector<ExtendedGUID>();

};

}

#endif
