/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <cassert>
#include "libone_utils.h"
#include "libone_types.h"
#include "OneNoteParser.h"
#include "Object.h"
#include "FileDataStore.h"
#include "TransactionLog.h"

namespace libone
{

libone::ExtendedGUID DataSignatureGroup = libone::ExtendedGUID();

OneNoteParser::OneNoteParser(const libone::RVNGInputStreamPtr_t &input, librevenge::RVNGDrawingInterface *const document)
{
  Header header = Header();
  libone::ExtendedGUID RootObject;

  header.parse(input);

  input->seek(0, librevenge::RVNG_SEEK_SET);

  ONE_DEBUG_MSG(("trying transactions, jumping to %ld\n", header.fcrTransactionLog.get_location()));
  input->seek(header.fcrTransactionLog.get_location(), librevenge::RVNG_SEEK_SET);



  ONE_DEBUG_MSG(("test fileNodeList\n"));
  parse_root_file_node_list(input, header, RootObject);
  ONE_DEBUG_MSG(("root object is %s\n", RootObject.to_string().c_str()));

  for (const auto &i: ObjectSpaces)
  {
    ONE_DEBUG_MSG(("object space %s\n", i.first.c_str()));
  }

  // TODO: replace with proper transaction implementation
  parse_transactions(input, header);

  ObjectSpaces[RootObject.to_string()].to_document(document);

  ONE_DEBUG_MSG(("nothing broke!\n"));

}

void OneNoteParser::parse_transactions(const libone::RVNGInputStreamPtr_t &input, Header &header)
{
  TransactionLog log = TransactionLog(header.fcrTransactionLog.get_location(),
                                      header.fcrTransactionLog.get_size(),
                                      header.cTransactionsInLog);
  log.parse(input);
}

void OneNoteParser::parse_root_file_node_list(const libone::RVNGInputStreamPtr_t &input,
                                              Header &header, ExtendedGUID &root_object)
{
  ExtendedGUID guid;
  std::vector<ObjectSpace> object_spaces = std::vector<ObjectSpace>();
  FileDataStore store;
  FileNodeList list(header.fcrFileNodeListRoot.get_location(), header.fcrFileNodeListRoot.get_size());
  (void) store;

  list.parse(input);

  DBMSG << "iterating on a " << list.get_fnd_list().size() << " size list" << std::endl;

  for (FileNode &node : list.get_fnd_list())
  {
    ObjectSpace object_space = ObjectSpace();
    DBMSG << node.to_string() << std::endl;

    switch (node.get_FileNodeID())
    {
    case FndId::ObjectSpaceManifestRootFND:
      input->seek(node.get_location() + node.header_size, librevenge::RVNG_SEEK_SET);
      root_object.parse(input);
      break;
    case FndId::ObjectSpaceManifestListReferenceFND:
      object_space.parse(input, node);
      break;
    case FndId::FileDataStoreListReferenceFND:
      break;
    case FndId::ObjectSpaceManifestListStartFND:
    case FndId::RevisionManifestListReferenceFND:
    case FndId::RevisionManifestListStartFND:
    case FndId::RevisionManifestStart4FND:
    case FndId::RevisionManifestEndFND:
    case FndId::RevisionManifestStart6FND:
    case FndId::RevisionManifestStart7FND:
    case FndId::GlobalIdTableStartFNDX:
    case FndId::GlobalIdTableStart2FND:
    case FndId::GlobalIdTableEntryFNDX:
    case FndId::GlobalIdTableEntry2FNDX:
    case FndId::GlobalIdTableEntry3FNDX:
    case FndId::GlobalIdTableEndFNDX:
    case FndId::ObjectDeclarationWithRefCountFNDX:
    case FndId::ObjectDeclarationWithRefCount2FNDX:
    case FndId::ObjectRevisionWithRefCountFNDX:
    case FndId::ObjectRevisionWithRefCount2FNDX:
    case FndId::RootObjectReference2FNDX:
    case FndId::RootObjectReference3FND:
    case FndId::RevisionRoleDeclarationFND:
    case FndId::RevisionRoleAndContextDeclarationFND:
    case FndId::ObjectDeclarationFileData3RefCountFND:
    case FndId::ObjectDeclarationFileData3LargeRefCountFND:
    case FndId::ObjectDataEncryptionKeyV2FNDX:
    case FndId::ObjectInfoDependencyOverridesFND:
    case FndId::DataSignatureGroupDefinitionFND:
    case FndId::FileDataStoreObjectReferenceFND:
    case FndId::ObjectDeclaration2RefCountFND:
    case FndId::ObjectDeclaration2LargeRefCountFND:
    case FndId::ObjectGroupListReferenceFND:
    case FndId::ObjectGroupStartFND:
    case FndId::ObjectGroupEndFND:
    case FndId::HashedChunkDescriptor2FND:
    case FndId::ReadOnlyObjectDeclaration2RefCountFND:
    case FndId::ReadOnlyObjectDeclaration2LargeRefCountFND:
    case FndId::ChunkTerminatorFND:
    case FndId::fnd_invalid_id:
    default:
      assert(false);
      break;
    }
  }

}

std::unordered_map<uint32_t, libone::GUID> GlobalIdentificationTable = std::unordered_map<uint32_t, libone::GUID>();

}
