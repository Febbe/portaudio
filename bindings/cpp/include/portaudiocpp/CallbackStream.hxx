#ifndef INCLUDED_PORTAUDIO_CALLBACKSTREAM_HXX
#define INCLUDED_PORTAUDIO_CALLBACKSTREAM_HXX

// ---------------------------------------------------------------------------------------

#include "portaudio.h"

#include "portaudiocpp/Stream.hxx"

// ---------------------------------------------------------------------------------------

// Declaration(s):
namespace portaudio
{
    /**
     * @brief Base class for all Streams which use a callback-based mechanism.
     */
    class CallbackStream : public Stream {
    public:
        CallbackStream(const CallbackStream &) = delete;
        CallbackStream &operator=(const CallbackStream &) = delete;
        CallbackStream(CallbackStream &&) = default;
        CallbackStream &operator=(CallbackStream &&) = default;
        
        ~CallbackStream() override = default;
    protected:
        CallbackStream() = default;

    public:
        // stream info (time-varying)
        double cpuLoad() const;
    };

} // namespace portaudio

// ---------------------------------------------------------------------------------------

#endif // INCLUDED_PORTAUDIO_CALLBACKSTREAM_HXX
