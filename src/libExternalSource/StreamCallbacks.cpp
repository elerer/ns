#include <StreamCallbacks.h>
#include <iostream>
#include <IBufferedProxyProcessor.h>
#include <cstdint>

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
    auto in = (int16_t *)inputBuffer;
    IBufferedProxyProcessor<int16_t> *pp = (IBufferedProxyProcessor<int16_t> *)userData;

    (void)outputBuffer; /* Prevent unused variable warning. */

    auto wa = pp->WriteAvailable();

    pp->Push(in, (unsigned long )wa >= framesPerBuffer  ? framesPerBuffer : wa);

    return 0;
}
