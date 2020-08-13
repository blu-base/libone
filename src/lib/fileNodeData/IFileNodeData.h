#ifndef IFILENODEDATA_H
#define IFILENODEDATA_H

#include <string>

#include "librevenge-stream/librevenge-stream.h"

namespace libone
{
class IFileNodeData
{
protected:
  IFileNodeData();

public:
  virtual ~IFileNodeData();

  friend librevenge::RVNGInputStream &operator>>(librevenge::RVNGInputStream &input, IFileNodeData &obj);

  virtual void parse(librevenge::RVNGInputStream &input) = 0;

  virtual std::string to_string() const = 0;


};

} // namespace libone

#endif // IFILENODEDATA_H

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
