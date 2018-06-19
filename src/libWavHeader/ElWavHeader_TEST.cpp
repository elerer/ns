#include "WavHeader.h"
#include "gmock/gmock.h"
#include <fstream>

using namespace testing;

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(WavHeader,creation)
{
  Wav_header wh;
  char buffer[1000];
  std::ifstream is("/home/eranl/WAV_FILES/attack.wav", std::ifstream::binary);
  is.read(buffer,1000);
  is.close();
  wh.FillHeader(buffer);

  ASSERT_THAT(std::string(wh._ChunkID,4),std::string("RIFF"));

}

TEST(WavHeader,normalize)
{
  char buffer[10000];
  std::ifstream is("/home/eranl/WAV_FILES/cello.wav", std::ifstream::binary);
  is.read(buffer,10000);
  is.close();
  Wav_header wh2;
  bool isModified = false;
  size_t origHeaderLength = 0;
  bool foundData = wh2.NormalizeWavHeaderOfBuffer(buffer,10000,origHeaderLength,isModified);

  std::cout << "orig header length " << origHeaderLength <<  '\n';

  ASSERT_THAT(foundData && isModified,true);

}

TEST(WavHeader,customDataLength)
{
  char buffer[10000];
  std::ifstream is("/home/eranl/WAV_FILES/cello.wav", std::ifstream::binary);
  is.read(buffer,10000);
  is.close();
  Wav_header wh2;
  bool isModified = false;
  size_t origHeaderLength = 0;

  bool foundData = wh2.NormalizeWavHeaderOfBuffer(buffer,10000,origHeaderLength,isModified);

  wh2.setSizeFieldsRelatedToDataLength(850);

  wh2.printHeader();

  ASSERT_THAT(850,wh2._Subchunk2Size);
  ASSERT_THAT(886,wh2._ChunkSize);

}
