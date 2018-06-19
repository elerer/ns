#include <WavFileSink.h>
#include<iostream>
WavFileSink::WavFileSink(const std::string &filename, const std::string &tmpPath, const std::string &path) :
 _filename(filename),
_tmpPath(tmpPath),
_path(path),
_fs(_tmpPath + _filename, std::ios::out | std::ios::binary | std::ios::ate)
{
    if (_fs.is_open())
    {
        std::cout << "file " << _tmpPath + _filename << " is open\n";
    }
}

WavFileSink::WavFileSink() : WavFileSink("def.wav", "/var/tmp/", "/var/tmp/")
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

void WavFileSink::Close()
{
    _fs.close();
}