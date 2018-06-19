#ifndef __ISTREAMSINK__
#define __ISTREAMSINK__
#include <cstdio>
//Interface for writeable stream.
class IStreamSink
{
public:
  virtual ~IStreamSink() {}
  virtual void StreamBytes(char *src, const size_t &num) = 0;
  virtual void Close() = 0; 
};
#endif