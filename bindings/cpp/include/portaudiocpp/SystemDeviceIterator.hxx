#ifndef INCLUDED_PORTAUDIO_SYSTEMDEVICEITERATOR_HXX
#define INCLUDED_PORTAUDIO_SYSTEMDEVICEITERATOR_HXX

// ---------------------------------------------------------------------------------------

#include <iterator>
#include <cstddef>

#include "portaudiocpp/System.hxx"

// ---------------------------------------------------------------------------------------

// Forward declaration(s):
namespace portaudio
{
    class Device;
    class HostApi;
}

// ---------------------------------------------------------------------------------------

// Declaration(s):
namespace portaudio
{


    //////
    /// @brief Iterator class for iterating through all Devices in a System.
    ///
    /// Devices will be iterated by iterating all Devices in each
    /// HostApi in the System. Compliant with the STL bidirectional
    /// iterator concept.
    //////
    class System::DeviceIterator
    {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = Device;
        using difference_type = ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        Device &operator*() const;
        Device *operator->() const;

        DeviceIterator &operator++();
        DeviceIterator operator++(int);
        DeviceIterator &operator--();
        DeviceIterator operator--(int);

        bool operator==(const DeviceIterator &rhs) const;
        bool operator!=(const DeviceIterator &rhs) const;

    private:
        friend class System;
        friend class HostApi;
        Device **ptr_;
    };


} // namespace portaudio

// ---------------------------------------------------------------------------------------

#endif // INCLUDED_PORTAUDIO_SYSTEMDEVICEITERATOR_HXX
