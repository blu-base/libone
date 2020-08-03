/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <iostream>
#include "libone_utils.h"

#include "ObjectSpace.h"

namespace libone
{

ObjectSpace::ObjectSpace()
{
}

void ObjectSpace::parse(librevenge::RVNGInputStream *input, FileNode &node)
{
  m_fnd_list_ref = node.get_fnd();

  FileNodeList list = FileNodeList(m_fnd_list_ref.get_location(), m_fnd_list_ref.get_size());

  // We should then be at the 'gosid' field
  input->seek(node.get_location() + node.header_size + m_fnd_list_ref.get_size_in_file(),
              librevenge::RVNG_SEEK_SET);

  input >> guid;

  list.parse(input);

  DBMSG << guid.to_string() << std::endl;

}

void ObjectSpace::list_parse(librevenge::RVNGInputStream *input, ExtendedGUID expected_guid, FileNodeChunkReference ref)
{
  Revision rev;
  FileNode node;
  FileNode node2;
  FileNodeList list = FileNodeList(ref.get_location(), ref.get_size());
  ExtendedGUID temp {};

  (void) expected_guid;

  list.parse(input);

  ONE_DEBUG_MSG(("trying to parse last revision\n"));
  rev.list_parse(input, node2.get_fnd());
  revisions.push_back(rev);
  ONE_DEBUG_MSG(("\n"));
}

void ObjectSpace::to_document(librevenge::RVNGDrawingInterface *document)
{
  (void) document;
  ONE_DEBUG_MSG(("\n"));
  for (auto i : revisions)
  {
    i.to_document(document);
  }
  ONE_DEBUG_MSG(("done?\n"));
}

std::string ObjectSpace::to_string()
{
  std::stringstream stream;
  stream << "ObjectSpace " << guid.to_string() << " context " << context.to_string() << " containing " << revisions.size() << " revisions\n";
  return stream.str();
}
}


