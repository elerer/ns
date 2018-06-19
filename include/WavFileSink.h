#ifndef __WAVFILESINK__
#define __WAVFILESINK__
#include <IStreamSink.h>
#include <string>
#include <WavHeader.h>
#include<fstream>
#include<string>
//implements a sink that writes wav files format
class WavFileSink : public IStreamSink
{
  public:
    WavFileSink(const std::string &filename, const std::string &tmpPath, const std::string &path);
    WavFileSink();
    ~WavFileSink();
    void StreamBytes(char *src, const size_t &num) override;
    void Close() override;

  private: /*methods*/
    void init();
  private: /*members*/
    //File location and name
    std::string _filename;
    std::string _tmpPath ;
    std::string _path ;

    Wav_header _wavHeader;
    std::ofstream _fs;
};
#endif