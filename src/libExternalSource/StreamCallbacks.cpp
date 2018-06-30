#include <StreamCallbacks.h>
#include <iostream>
#include <IBufferedProxyProcessor.h>
#include <cstdint>
#include <fstream>
#include <algorithm>

int TestStreamInputSource(const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo *timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData)
{
    /* Cast data passed through stream to our structure. */
    auto *in = (float *)inputBuffer;
    unsigned int i;
    (void)outputBuffer; /* Prevent unused variable warning. */

    for (i = 0; i < framesPerBuffer; i++)
    {
        float left = *in++;
        float right = *in++;
        std::cout << "l [" << left << "] r [" << right << "]\n";
        //write samples to user data,
    }
    return 0;
}

int Int16ProxyInputSource(const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo *timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData)
{
   
    /* Cast data passed through stream to our structure. */
    int16_t *in = (int16_t *)inputBuffer;

    IBufferedProxyProcessor<int16_t> *pp = (IBufferedProxyProcessor<int16_t> *)userData;

    (void)outputBuffer; /* Prevent unused variable warning. */

    auto wa = (unsigned long)pp->WriteAvailable();

    size_t factor = 2; //num of channels * ?

    auto ftw = ((wa >= framesPerBuffer) ? framesPerBuffer : wa) * factor;

    auto nw = (unsigned long)pp->Push(in, ftw);

    if (nw < ftw)
    {
        std::cout << "needed to write " << ftw << " wrote only " << nw << "\n";
    }

    return 0;
}

int Int24ProxyInputSource(const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo *timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData)
{
    /* Cast data passed through stream to our structure. */
    auto in = (s24bit *)inputBuffer;
    IBufferedProxyProcessor<s24bit> *pp = (IBufferedProxyProcessor<s24bit> *)userData;

    (void)outputBuffer; /* Prevent unused variable warning. */

    auto wa = (unsigned long)pp->WriteAvailable();

    size_t factor = 2 ; //num of channels * ?

    auto ftw = ((wa >= framesPerBuffer) ? framesPerBuffer : wa) * factor;

    auto nw = (unsigned long)pp->Push(in, ftw);

    if (nw < ftw)
    {
        std::cout << "needed to write " << ftw << " wrote only " << nw << "\n";
    }
    return 0;
}
