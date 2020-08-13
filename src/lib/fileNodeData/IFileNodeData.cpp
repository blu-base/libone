#include "IFileNodeData.h"

namespace libone
{
IFileNodeData::IFileNodeData() {}

IFileNodeData::~IFileNodeData() {}

librevenge::RVNGInputStream &operator>>(librevenge::RVNGInputStream &input, IFileNodeData &obj)
{
  obj.parse(input);
  return input;
}

} // namespace libone
/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
