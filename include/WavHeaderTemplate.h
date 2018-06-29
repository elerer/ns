#ifndef __WAVHEADERTEMPLATE__
#define __WAVHEADERTEMPLATE__
#include <WavHeader.h>
#include <string>
class WavHeaderTemplate
{
  public:
    WavHeaderTemplate(const std::string &templateSource);
    void SetTemplate(const size_t &nc, const size_t &sr, const size_t &bitrate, const size_t &audioByteSize);
    const char *const GetHeaderBuffer();
    const size_t Wav_header_Size = 44;

  private: /*methods*/
    void setNumChannels(const size_t &nc);

    void setSampleRate(const size_t &sr);

    void setBitRate(const size_t &br);

    void setAudioSize(const size_t &audioSize);

  private: /*members*/
    Wav_header _wavHeader;
    const size_t _wavHeaderSize = 44;
};
#endif