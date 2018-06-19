#include"WavHeader.h"
#include<string>
#include<string.h>
#include<iostream>

void Wav_header::FillHeader(const char* buffer)
{
  setChunkId(buffer);
  setChunkSize(buffer);
  setFormat(buffer);
  setSubchunk1ID(buffer);
  setSubchunk1Size(buffer);
  setAudioFormat(buffer);
  setNumChannels(buffer);
  setSampleRate(buffer);
  setByteRate(buffer);
  setBlockAlign(buffer);
  setBitsPerSample(buffer);
  setSubchunk2ID(buffer);
  setSubchunk2Size(buffer);
  //printHeader();
}

void Wav_header::printHeader()
{
  std::cout << "HEADER:" << '\n';
  printChunkID();
  printChunkSize();
  printFormat();
  printSubchunk1ID();
  printSubchunk1Size();
  printAudioFormat();
  printNumChannels();
  printSampleRate();
  printByteRate();
  printBlockAlign();
  printBitsPerSample();
  printSubchunk2ID();
  printSubchunk2Size();
}


//If we want to control the size of the wav header data
void Wav_header::setSizeFieldsRelatedToDataLength(const int32_t& length)
{
  int32_t newLength = length + 44 - 8;//44 is header size
  memcpy(&_ChunkSize,(char*)&newLength,4);
  memcpy(&_Subchunk2Size,(char*)&length,4);
}

bool Wav_header::NormalizeWavHeaderOfBuffer(char* buffer,const size_t& length,size_t& totalSizeBeforeReduction,bool& modifiedBuffer)
{
  totalSizeBeforeReduction = 0;
  size_t offset = 36;//offset of _Subchunk2Size
  FillHeader(buffer);
  bool retval = false;
  if (std::string(_Subchunk2ID,4) != "data")
  {
    std::cout << "--------heder no valid-------" << '\n';
    printHeader();
    size_t newOffset = offset;
    while(newOffset + 4 < length )
    {
      if(buffer[newOffset] == 'd')
      {
        if (std::string((buffer + newOffset),4) == "data")
        {
          memcpy(buffer+offset,buffer+newOffset,length-newOffset);
          FillHeader(buffer);
          std::cout << "--------Modified heder-------" << '\n';
          printHeader();
          modifiedBuffer = true;
          retval = true;
          totalSizeBeforeReduction = newOffset + 4 + 4;// =8 bytes from the beginning of the 'd' of data
          break;
        }
      }
      newOffset++;
    }
  }
  else
  {
    retval = true;
    totalSizeBeforeReduction = 44;
  }

  return retval;
}

void Wav_header::setChunkId(const char* buffer)
{
  memcpy(_ChunkID,buffer,4);
}
void Wav_header::printChunkID()
{
  std::cout << std::string(_ChunkID,4) << '\n';
}

void Wav_header::setChunkSize(const char* buffer)
{
  memcpy(&_ChunkSize,buffer+4,4);
}
void Wav_header::printChunkSize()
{
  std::cout << _ChunkSize << '\n';
}

void Wav_header::setFormat(const char* buffer)
{
  memcpy(_Format,buffer+8,4);
}
void Wav_header::printFormat()
{
  std::cout << std::string(_Format,4) << '\n';
}

void Wav_header::setSubchunk1ID(const char* buffer)
{
  memcpy(_Subchunk1ID,buffer+12,4);
}
void Wav_header::printSubchunk1ID()
{
  std::cout << std::string(_Subchunk1ID,4) << '\n';
}

void Wav_header::setSubchunk1Size(const char* buffer)
{
  memcpy(&_Subchunk1Size,buffer+16,4);
}
void Wav_header::printSubchunk1Size()
{
  std::cout << _Subchunk1Size << '\n';
}

void Wav_header::setAudioFormat(const char* buffer)
{
  memcpy(&_AudioFormat,buffer+20,2);
}
void Wav_header::printAudioFormat()
{
  std::cout << "AudioFormat(PCM):" << _AudioFormat << '\n';
}

void Wav_header::setNumChannels(const char* buffer)
{
  memcpy(&_NumChannels,buffer+22,2);
}
void Wav_header::printNumChannels()
{
  std::cout << "Num of channels: " << _NumChannels << '\n';
}

void Wav_header::setSampleRate(const char* buffer)
{
  memcpy(&_SampleRate,buffer+24,4);
}
void Wav_header::printSampleRate()
{
  std::cout << "SampleRate: " << _SampleRate << '\n';
}

void Wav_header::setByteRate(const char* buffer)
{
  memcpy(&_ByteRate,buffer+28,4);
}
void Wav_header::printByteRate()
{
  std::cout << "ByteRate: " << _ByteRate << '\n';
}

void Wav_header::setBlockAlign(const char* buffer)
{
  memcpy(&_BlockAlign,buffer+32,2);
}
void Wav_header::printBlockAlign()
{
  std::cout << "BlockAlign: " << _BlockAlign << '\n';
}

void Wav_header::setBitsPerSample(const char* buffer)
{
  memcpy(&_BitsPerSample,buffer+34,2);
}
void Wav_header::printBitsPerSample()
{
  std::cout << "BitsPerSample: " << _BitsPerSample << '\n';
}

void Wav_header::setSubchunk2ID(const char* buffer)
{
  memcpy(_Subchunk2ID,buffer+36,4);
}
void Wav_header::printSubchunk2ID()
{
  std::cout << std::string(_Subchunk2ID,4) << '\n';
}

void Wav_header::setSubchunk2Size(const char* buffer)
{
  memcpy(&_Subchunk2Size,buffer+40,4);
}

void Wav_header::printSubchunk2Size()
{
  std::cout << "Subchunk2Size: " << _Subchunk2Size << '\n';
}
