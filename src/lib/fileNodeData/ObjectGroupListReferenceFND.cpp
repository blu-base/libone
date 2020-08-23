#include "ObjectGroupListReferenceFND.h"

namespace libone
{

ObjectGroupListReferenceFND::ObjectGroupListReferenceFND(
  StpFormat stpFormat, CbFormat cbFormat)
  : m_ref(stpFormat, cbFormat), m_ObjectGroupID() {}

ExtendedGUID ObjectGroupListReferenceFND::objectGroupID() const
{
  return m_ObjectGroupID;
}

void ObjectGroupListReferenceFND::setObjectGroupID(
  const ExtendedGUID &objectGroupID)
{
  m_ObjectGroupID = objectGroupID;
}

FileNodeChunkReference ObjectGroupListReferenceFND::ref() const
{
  return m_ref;
}

void ObjectGroupListReferenceFND::setRef(const FileNodeChunkReference &ref)
{
  m_ref = ref;
}

void ObjectGroupListReferenceFND::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_ref;
  input >> m_ObjectGroupID;
}

std::string ObjectGroupListReferenceFND::to_string() const
{
  return "";
}

std::unique_ptr<IFileNodeData> ObjectGroupListReferenceFND::clone() const
{
  return std::make_unique<ObjectGroupListReferenceFND>(*this);
}
} // namespace libone
