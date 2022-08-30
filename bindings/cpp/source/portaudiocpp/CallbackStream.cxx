#include "portaudiocpp/CallbackStream.hxx"

namespace portaudio
{
    double CallbackStream::cpuLoad() const
    {
        return Pa_GetStreamCpuLoad(stream_);
    }

} // namespace portaudio
