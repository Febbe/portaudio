#ifndef INCLUDED_PORTAUDIO_SYSTEMHOSTAPIITERATOR_HXX
#define INCLUDED_PORTAUDIO_SYSTEMHOSTAPIITERATOR_HXX

// ---------------------------------------------------------------------------------------

#include <iterator>
#include <cstddef>

#include "portaudiocpp/System.hxx"

// ---------------------------------------------------------------------------------------

// Forward declaration(s):
namespace portaudio
{
    class HostApi;
}

// ---------------------------------------------------------------------------------------

// Declaration(s):
namespace portaudio
{


    //////
    /// @brief Iterator class for iterating through all HostApis in a System.
    ///
    /// Compliant with the STL bidirectional iterator concept.
    //////
    class System::HostApiIterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag ;
        using value_type = Device;
        using difference_type = ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        HostApi &operator*() const;
        HostApi *operator->() const;

        HostApiIterator &operator++();
        HostApiIterator operator++(int);
        HostApiIterator &operator--();
        HostApiIterator operator--(int);

        bool operator==(const HostApiIterator &rhs) const;
        bool operator!=(const HostApiIterator &rhs) const;

    private:
        friend class System;
        HostApi **ptr_;
    };


} // namespace portaudio

// ---------------------------------------------------------------------------------------

#endif // INCLUDED_PORTAUDIO_SYSTEMHOSTAPIITERATOR_HXX
