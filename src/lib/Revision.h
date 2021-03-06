/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_REVISION_H
#define INCLUDED_LIBONE_REVISION_H

#include <string>
#include <librevenge-stream/librevenge-stream.h>
#include <unordered_map>

#include "Object.h"
#include "ObjectGroup.h"


namespace libone
{

class Revision
{
public:
  void list_parse(const libone::RVNGInputStreamPtr_t &input, FileNodeChunkReference ref);
  std::string get_guid();
  std::string to_string();
  ObjectGroup group = ObjectGroup();
  void to_document(librevenge::RVNGDrawingInterface *document);
private:
  ExtendedGUID guid = ExtendedGUID();
  ExtendedGUID dependent = ExtendedGUID();
  ExtendedGUID root_object = ExtendedGUID();
  std::unordered_map<std::string, uint32_t> root_objects = std::unordered_map<std::string, uint32_t>();
  std::unordered_map<std::string, Object> objects = std::unordered_map<std::string, Object>();
  bool read_only = false;
  unsigned int ref_count = 0;
  uint32_t role = 0;
  uint16_t odcsDefault = 0;
  ExtendedGUID context = ExtendedGUID();
  void parse_dependencies(const libone::RVNGInputStreamPtr_t &input, FileNode node);

};

}

#endif
