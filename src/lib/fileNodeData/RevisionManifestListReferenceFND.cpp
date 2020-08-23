#include "RevisionManifestListReferenceFND.h"

namespace libone
{

RevisionManifestListReferenceFND::RevisionManifestListReferenceFND(
  StpFormat stpFormat, CbFormat cbFormat)
  : m_ref(stpFormat, cbFormat) {}
RevisionManifestListReferenceFND::~RevisionManifestListReferenceFND() {}

FileNodeChunkReference RevisionManifestListReferenceFND::getRef() const
{
  return m_ref;
}

void RevisionManifestListReferenceFND::setRef(
  const FileNodeChunkReference &value)
{
  m_ref = value;
}

void RevisionManifestListReferenceFND::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_ref;
}

std::string RevisionManifestListReferenceFND::to_string() const
{
  return "";
}

std::unique_ptr<IFileNodeData> RevisionManifestListReferenceFND::clone() const
{
  return std::make_unique<RevisionManifestListReferenceFND>(*this);
}
} // namespace libone
