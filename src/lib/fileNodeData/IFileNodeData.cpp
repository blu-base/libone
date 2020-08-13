#include "IFileNodeData.h"

namespace libone
{
IFileNodeData::IFileNodeData() {}

IFileNodeData::~IFileNodeData() {}

const libone::RVNGInputStreamPtr_t &operator>>(const libone::RVNGInputStreamPtr_t &input, IFileNodeData &obj)
{
  obj.parse(input);
  return input;
}

} // namespace libone

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
