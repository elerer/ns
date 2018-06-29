#include <WavHeaderTemplate.h>
#include <fstream>

WavHeaderTemplate::WavHeaderTemplate(const std::string &templateSource)
{
    char buffer[1000];
    std::ifstream is(templateSource.c_str(), std::ifstream::binary);
    is.read(buffer, 1000);
    is.close();
    _wavHeader.FillHeader(buffer);
}

void WavHeaderTemplate::SetTemplate(const size_t &nc, const size_t &sr, const size_t &bitrate, const size_t &audioByteSize)
{
    setNumChannels(nc);
    setSampleRate(sr);
    setBitRate(bitrate);
    _wavHeader._ByteRate = nc * sr * bitrate / 8;
    setAudioSize(audioByteSize);
}

void WavHeaderTemplate::setNumChannels(const size_t &nc)
{
    _wavHeader._NumChannels = nc;
}

void WavHeaderTemplate::setSampleRate(const size_t &sr)
{
    _wavHeader._SampleRate = sr;
}

void WavHeaderTemplate::setBitRate(const size_t &br)
{
    _wavHeader._BitsPerSample = br;
}

void WavHeaderTemplate::setAudioSize(const size_t &audioSize)
{
    _wavHeader._Subchunk2Size = audioSize;
    _wavHeader._ChunkSize = audioSize + 36;
}

const char* const WavHeaderTemplate::GetHeaderBuffer()
{
    return (char*)&_wavHeader;
}