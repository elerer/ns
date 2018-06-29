#include <WavFileSink.h>
#include <iostream>
WavFileSink::WavFileSink(const size_t &numchannels, const size_t &samplerate, const size_t &bitrate,
                         const std::string &filename, const std::string &tmpPath, const std::string &path) : _numchannels(numchannels),
                                                                                                             _samplerate(samplerate),
                                                                                                             _bitrate(bitrate),
                                                                                                             _filename(filename),
                                                                                                             _tmpPath(tmpPath),
                                                                                                             _path(path),
                                                                                                             _fs(_tmpPath + _filename, std::ios::out | std::ios::binary | std::ios::ate),
                                                                                                             _ht("/home/eranl/WAV_FILES/attack.wav")
{
    if (_fs.is_open())
    {
        std::cout << "file " << _tmpPath + _filename << " is open\n";
    }
}

WavFileSink::WavFileSink(const size_t &numchannels, const size_t &samplerate, const size_t &bitrate) : WavFileSink(numchannels, samplerate, bitrate, "def.wav", "/var/tmp/", "/home/eranl/WAV_FILES/")
{
}

WavFileSink::~WavFileSink()
{
    Close();
}
void WavFileSink::StreamBytes(char *src, const size_t &num)
{
    _fs.write(src, num);
}

void WavFileSink::Run()
{

}
void WavFileSink::Close()
{
    if (_fs.is_open())
    {
        size_t fsize = _fs.tellp();
        _fs.close();
        writeWavFromTmpFile(fsize);
        
    }
}

void WavFileSink::writeWavFromTmpFile(size_t fsize)
{
    _ht.SetTemplate(_numchannels, _samplerate, _bitrate, fsize);
    std::ifstream fsi (_tmpPath + _filename, std::ios::in | std::ios::binary);
    //open final file write header and then tmp file content.
    std::ofstream fso(_path + _filename, std::ios::out | std::ios::binary | std::ios::ate);
    if (!fso.is_open())
    {
        std::cout << "couldnt open file " << _path + _filename << "\n";
        return;
    }
    fso.write(_ht.GetHeaderBuffer(), _ht.Wav_header_Size);
    char buffer[256];
    fsi.seekg(0);
    size_t bn = 0;
    while(fsize > 0)
    {
        bn = fsize > 256 ? 256 : fsize;
        fsize -= bn;
        fsi.read(buffer,bn);
        fso.write(buffer,bn);
    }
    fso.close();

}