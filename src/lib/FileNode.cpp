/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <cassert>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <libone/libone.h>

#include "libone_utils.h"

#include <bitset>

#include "FileNode.h"
#include "fileNodeData/FileNodeData.h"

namespace libone
{

FileNode::~FileNode()
{
}
FileNode::FileNode() : m_fncr(), m_fnd_id(FndId::fnd_invalid_id), m_base_type(fnd_invalid_basetype),
  m_fnd(nullptr)
{
}

FileNode::FileNode(const FileNode &obj) :
  m_fncr(obj.m_fncr), m_fnd_id(obj.m_fnd_id), m_base_type(obj.m_base_type)
{
  if (obj.get_fnd() != nullptr)
  {
    m_fnd = obj.m_fnd->clone();
  }
  else
  {
    m_fnd = nullptr;
  }

}

FileNode &FileNode::operator=(const FileNode &rhs)
{
  m_fncr = rhs.m_fncr;
  m_fnd_id = rhs.m_fnd_id;
  m_base_type = rhs.m_base_type;

  m_fnd = rhs.m_fnd->clone();
  return *this;
}
FileNode &FileNode::operator=(FileNode &&rhs)
{
  m_fncr = rhs.m_fncr;
  m_fnd_id = rhs.m_fnd_id;
  m_base_type = rhs.m_base_type;

  m_fnd = std::move(rhs.m_fnd);
  return *this;
}


std::string fnd_id_to_string(FndId id_fnd)
{
  std::stringstream stream;

  switch (id_fnd)
  {
  case FndId::ObjectSpaceManifestListStartFND:
    stream << "ObjectSpaceManifestListStartFND";
    break;
  case FndId::ChunkTerminatorFND:
    stream << "ChunkTerminatorFND";
    break;
  case FndId::RevisionManifestListStartFND:
    stream << "RevisionManifestListStart";
    break;
  case FndId::RevisionManifestStart4FND:
    stream << "RevisionManifestStart4FND";
    break;
  case FndId::RevisionManifestStart6FND:
    stream << "RevisionManifestStart6FND";
    break;
  case FndId::RevisionManifestStart7FND:
    stream << "RevisionManifestStart";
    break;
  case FndId::RevisionManifestListReferenceFND:
    stream << "RevisionManifestListReferenceFND";
    break;
  case FndId::ObjectGroupListReferenceFND:
    stream << "ObjectGroupListReferenceFND";
    break;
  case FndId::ObjectSpaceManifestListReferenceFND:
    stream << "ObjectSpaceManifestListReferenceFND";
    break;
  case FndId::ObjectSpaceManifestRootFND:
    stream << "ObjectSpaceManifestListRootFND";
    break;
  case FndId::FileDataStoreListReferenceFND:
    stream << "FileDataStoreListReferenceFND";
    break;
  case FndId::ObjectGroupStartFND:
    stream << "ObjectGroupStartFND";
    break;
  case FndId::GlobalIdTableStart2FND:
    stream << "GlobalIdTableStart2FND";
    break;
  case FndId::GlobalIdTableEntryFNDX:
    stream << "GlobalIdTableEntryFNDX";
    break;
  case FndId::GlobalIdTableEndFNDX:
    stream << "GlobalIdTableEndFNDX";
    break;
  case FndId::DataSignatureGroupDefinitionFND:
    stream << "DataSignatureGroupDefinitionFND";
    break;
  case FndId::ObjectDeclaration2RefCountFND:
    stream << "ObjectDeclaration2RefCountFND";
    break;
  case FndId::ObjectGroupEndFND:
    stream << "ObjectGroupEndFND";
    break;
  case FndId::RevisionManifestEndFND:
    stream << "RevisionManifestEndFND";
    break;
  case FndId::GlobalIdTableStartFNDX:
    stream << "GlobalIdTableStartFNDX";
    break;
  case FndId::GlobalIdTableEntry2FNDX:
    stream << "GlobalIdTableEntry2FNDX";
    break;
  case FndId::GlobalIdTableEntry3FNDX:
    stream << "GlobalIdTableEntry3FNDX";
    break;
  case FndId::ObjectDeclarationWithRefCountFNDX:
    stream << "ObjectDeclarationWithRefCountFNDX";
    break;
  case FndId::ObjectDeclarationWithRefCount2FNDX:
    stream << "ObjectDeclarationWithRefCount2FNDX";
    break;
  case FndId::ObjectRevisionWithRefCountFNDX:
    stream << "ObjectRevisionWithRefCountFNDX";
    break;
  case FndId::ObjectRevisionWithRefCount2FNDX:
    stream << "ObjectRevisionWithRefCount2FNDX";
    break;
  case FndId::RootObjectReference2FNDX:
    stream << "RootObjectReference2FNDX";
    break;
  case FndId::RootObjectReference3FND:
    stream << "RootObjectReference3FND";
    break;
  case FndId::RevisionRoleDeclarationFND:
    stream << "RevisionRoleDeclarationFND";
    break;
  case FndId::RevisionRoleAndContextDeclarationFND:
    stream << "RevisionRoleAndContextDeclarationFND";
    break;
  case FndId::ObjectDeclarationFileData3RefCountFND:
    stream << "ObjectDeclarationFileData3RefCountFND";
    break;
  case FndId::ObjectDeclarationFileData3LargeRefCountFND:
    stream << "ObjectDeclarationFileData3LargeRefCountFND";
    break;
  case FndId::ObjectDataEncryptionKeyV2FNDX:
    stream << "ObjectDataEncryptionKeyV2FNDX";
    break;
  case FndId::ObjectInfoDependencyOverridesFND:
    stream << "ObjectInfoDependencyOverridesFND";
    break;
  case FndId::FileDataStoreObjectReferenceFND:
    stream << "FileDataStoreObjectReferenceFND";
    break;
  case FndId::ObjectDeclaration2LargeRefCountFND:
    stream << "ObjectDeclaration2LargeRefCountFND";
    break;
  case FndId::HashedChunkDescriptor2FND:
    stream << "HashedChunkDescriptor2FND";
    break;
  case FndId::ReadOnlyObjectDeclaration2RefCountFND:
    stream << "ReadOnlyObjectDeclaration2RefCountFND";
    break;
  case FndId::ReadOnlyObjectDeclaration2LargeRefCountFND:
    stream << "ReadOnlyObjectDeclaration2LargeRefCountFND";
    break;
  case FndId::fnd_invalid_id:
  default:
    stream << "Invalid FND";
    break;
  }
  return stream.str();
}

void FileNode::parse(const libone::RVNGInputStreamPtr_t &input)
{
  parse_header(input);

  switch (m_fnd_id)
  {
  case FndId::DataSignatureGroupDefinitionFND:
    m_fnd = std::make_unique<DataSignatureGroupDefinitionFND>();
    break;
  case FndId::FileDataStoreListReferenceFND:
    m_fnd = std::make_unique<FileDataStoreListReferenceFND>(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::FileDataStoreObjectReferenceFND:
    m_fnd = std::make_unique<FileDataStoreObjectReferenceFND>(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::GlobalIdTableEntry2FNDX:
    m_fnd = std::make_unique<GlobalIdTableEntry2FNDX>();
    break;
  case FndId::GlobalIdTableEntry3FNDX:
    m_fnd = std::make_unique<GlobalIdTableEntry3FNDX>();
    break;
  case FndId::GlobalIdTableEntryFNDX:
    m_fnd = std::make_unique<GlobalIdTableEntryFNDX>();
    break;
  case FndId::GlobalIdTableStartFNDX:
    m_fnd = std::make_unique<GlobalIdTableStartFNDX>();
    break;
  case FndId::HashedChunkDescriptor2FND:
    m_fnd = std::make_unique<HashedChunkDescriptor2FND>(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::ObjectDataEncryptionKeyV2FNDX:
    m_fnd = std::make_unique<ObjectDataEncryptionKeyV2FNDX>(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::ObjectDeclaration2LargeRefCountFND:
    m_fnd = std::make_unique<ObjectDeclaration2LargeRefCountFND>(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::ObjectDeclaration2RefCountFND:
    m_fnd = std::make_unique<ObjectDeclaration2RefCountFND>(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::ObjectDeclarationFileData3LargeRefCountFND:
    m_fnd = std::make_unique<ObjectDeclarationFileData3LargeRefCountFND>();
    break;
  case FndId::ObjectDeclarationFileData3RefCountFND:
    m_fnd = std::make_unique<ObjectDeclarationFileData3RefCountFND>();
    break;
  case FndId::ObjectDeclarationWithRefCount2FNDX:
    m_fnd = std::make_unique<ObjectDeclarationWithRefCount2FNDX>(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::ObjectDeclarationWithRefCountFNDX:
    m_fnd = std::make_unique<ObjectDeclarationWithRefCountFNDX>(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::ObjectGroupListReferenceFND:
    m_fnd = std::make_unique<ObjectGroupListReferenceFND>(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::ObjectGroupStartFND:
    m_fnd = std::make_unique<ObjectGroupStartFND>();
    break;
  case FndId::ObjectInfoDependencyOverridesFND:
    m_fnd = std::make_unique<ObjectInfoDependencyOverridesFND>(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::ObjectRevisionWithRefCount2FNDX:
    m_fnd = std::make_unique<ObjectRevisionWithRefCount2FNDX>(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::ObjectRevisionWithRefCountFNDX:
    m_fnd = std::make_unique<ObjectRevisionWithRefCountFNDX>(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::ObjectSpaceManifestListReferenceFND:
    m_fnd = std::make_unique<ObjectSpaceManifestListReferenceFND>(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::ObjectSpaceManifestListStartFND:
    m_fnd = std::make_unique<ObjectSpaceManifestListStartFND>();
    break;
  case FndId::ObjectSpaceManifestRootFND:
    m_fnd = std::make_unique<ObjectSpaceManifestRootFND>();
    break;
  case FndId::ReadOnlyObjectDeclaration2LargeRefCountFND:
    m_fnd = std::make_unique<ReadOnlyObjectDeclaration2LargeRefCountFND>(m_fncr.get_stp_fmt(),
                                                                         m_fncr.get_cb_fmt());
    break;
  case FndId::ReadOnlyObjectDeclaration2RefCountFND:
    m_fnd = std::make_unique<ReadOnlyObjectDeclaration2RefCountFND>(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::RevisionManifestListReferenceFND:
    m_fnd = std::make_unique<RevisionManifestListReferenceFND>(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::RevisionManifestListStartFND:
    m_fnd = std::make_unique<RevisionManifestListStartFND>();
    break;
  case FndId::RevisionManifestStart4FND:
    m_fnd = std::make_unique<RevisionManifestStart4FND>();
    break;
  case FndId::RevisionManifestStart6FND:
    m_fnd = std::make_unique<RevisionManifestStart6FND>();
    break;
  case FndId::RevisionManifestStart7FND:
    m_fnd = std::make_unique<RevisionManifestStart7FND>();
    break;
  case FndId::RevisionRoleAndContextDeclarationFND:
    m_fnd = std::make_unique<RevisionRoleAndContextDeclarationFND>();
    break;
  case FndId::RevisionRoleDeclarationFND:
    m_fnd = std::make_unique<RevisionRoleDeclarationFND>();
    break;
  case FndId::RootObjectReference2FNDX:
    m_fnd = std::make_unique<RootObjectReference2FNDX>();
    break;
  case FndId::RootObjectReference3FND:
    m_fnd = std::make_unique<RootObjectReference3FND>();
    break;

  // nodes without data
  case FndId::RevisionManifestEndFND:
  case FndId::GlobalIdTableStart2FND:
  case FndId::GlobalIdTableEndFNDX:
  case FndId::ObjectGroupEndFND:
  case FndId::ChunkTerminatorFND:
  case FndId::fnd_invalid_id:
  default:
    break;
  }

  if (m_fnd != nullptr)
  {
    input >> *m_fnd.get();
  }

}

std::string FileNode::to_string() const
{
  std::stringstream stream;

  stream << fnd_id_to_string(m_fnd_id);
  stream << "; ";

  stream << std::hex << "base_type ";
  switch (m_base_type)
  {
  case fnd_no_data:
    stream << "fnd_no_data";
    break;
  case fnd_ref_data:
    stream << "fnd_ref_data@0x" << m_fncr.stp();
    break;
  case fnd_ref_filenodelist:
    stream << "fnd_ref_filenodelist@0x" << m_fncr.stp();
    break;
  case fnd_invalid_basetype:
  default:
    stream << "UNKNOWN BASETYPE";
    assert(false);
    break;
  }

  return stream.str();
}

void FileNode::parse_header(const libone::RVNGInputStreamPtr_t &input)
{
  uint64_t stp = input->tell();
  uint32_t temp;

  input >> temp;

  StpFormat stp_format = static_cast<StpFormat>((temp >> shift_format_stp) & mask_format_stp);
  CbFormat cb_format = static_cast<CbFormat>((temp >> shift_format_cb) & mask_format_cb);
  m_base_type = static_cast<fnd_basetype>((temp >> shift_base_type) & mask_fnd_base_type);
  m_fnd_id = static_cast<FndId>(temp & mask_fnd_id);
  uint32_t cb  = (temp >> shift_fnd_size) & mask_fnd_size;

  m_fncr = FileNodeChunkReference(stp, cb, stp_format, cb_format);

}

}


