#ifndef INCLUDED_PORTAUDIO_INTERFACECALLBACKSTREAM_HXX
#define INCLUDED_PORTAUDIO_INTERFACECALLBACKSTREAM_HXX

// ---------------------------------------------------------------------------------------

#include "portaudio.h"

#include "portaudiocpp/CallbackStream.hxx"

// ---------------------------------------------------------------------------------------

// Forward declaration(s)
namespace portaudio
{
    class StreamParameters;
    class CallbackInterface;
}

// ---------------------------------------------------------------------------------------

// Declaration(s):
namespace portaudio
{
    //////
    /// @brief Callback stream using an instance of an object that's derived from the CallbackInterface
    /// interface.
    //////
    class InterfaceCallbackStream final : public CallbackStream {
    public:
        InterfaceCallbackStream() = default;
        InterfaceCallbackStream(const StreamParameters &parameters, CallbackInterface &instance);
        ~InterfaceCallbackStream();

        InterfaceCallbackStream(const InterfaceCallbackStream &) = delete;
        InterfaceCallbackStream &operator=(const InterfaceCallbackStream &) = delete; 
        InterfaceCallbackStream(InterfaceCallbackStream &&) = default;
        InterfaceCallbackStream &operator=(InterfaceCallbackStream &&) = default;

        void open(const StreamParameters &parameters, CallbackInterface &instance);
    };

} // portaudio

// ---------------------------------------------------------------------------------------

#endif // INCLUDED_PORTAUDIO_INTERFACECALLBACKSTREAM_HXX
