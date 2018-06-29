#ifndef __WAVFILESINK__
#define __WAVFILESINK__
#include <IStreamSink.h>
#include <string>
#include <WavHeaderTemplate.h>
#include <fstream>
#include <string>
//implements a sink that writes wav files format
class WavFileSink : public IStreamSink
{
public:
  WavFileSink(const size_t &numchannels, const size_t &samplerate, const size_t &bitrate,
              const std::string &filename, const std::string &tmpPath, const std::string &path);
  WavFileSink(const size_t &numchannels, const size_t &samplerate, const size_t &bitrate);
  ~WavFileSink();
  void StreamBytes(char *src, const size_t &num) override;
  void Close() override;
  void Run()  override;

private: /*methods*/
  void init();
  void writeWavFromTmpFile(size_t fsize);

private: /*members*/
  //File location and name
  size_t _numchannels = 0;
  size_t _samplerate = 0;
  size_t _bitrate = 0;
  std::string _filename;
  std::string _tmpPath;
  std::string _path;
  std::ofstream _fs;
  

  WavHeaderTemplate _ht;
};
#endif