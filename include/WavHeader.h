#include <stdint.h>
#include <cstdlib>

struct Wav_header
{
public:
  void FillHeader(const char* buffer);
  bool NormalizeWavHeaderOfBuffer(char* buffer,const size_t& length,size_t& totalSizeBeforeReduction,bool& modifiedBuffer);
  void setSizeFieldsRelatedToDataLength(const int32_t& length);
  void printHeader();

//METHODS//
  void setChunkId(const char* buffer);
  void printChunkID();

  void setChunkSize(const char* buffer);
  void printChunkSize();

  void setFormat(const char* buffer);
  void printFormat();
  void setSubchunk1ID(const char* buffer);
  void printSubchunk1ID();
  void setSubchunk1Size(const char* buffer);
  void printSubchunk1Size();
  void setAudioFormat(const char* buffer);
  void printAudioFormat();
  void setNumChannels(const char* buffer);
  void printNumChannels();
  void setSampleRate(const char* buffer);
  void printSampleRate();
  void setByteRate(const char* buffer);
  void printByteRate();
  void setBlockAlign(const char* buffer);
  void printBlockAlign();
  void setBitsPerSample(const char* buffer);
  void printBitsPerSample();
  void setSubchunk2ID(const char* buffer);
  void printSubchunk2ID();
  void setSubchunk2Size(const char* buffer);
  void printSubchunk2Size();

  char _ChunkID[4];
  int32_t _ChunkSize;
  char _Format[4];
  char _Subchunk1ID[4];
  int32_t _Subchunk1Size;
  int16_t _AudioFormat;
  int16_t _NumChannels;
  int32_t _SampleRate;
  int32_t _ByteRate;
  int16_t _BlockAlign;
  int16_t _BitsPerSample;
  char _Subchunk2ID[4];
  int32_t _Subchunk2Size;


};
