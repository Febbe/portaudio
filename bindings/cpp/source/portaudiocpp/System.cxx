#include "portaudiocpp/System.hxx"

#include <cstddef>
#include <cassert>

#include "portaudiocpp/HostApi.hxx"
#include "portaudiocpp/Device.hxx"
#include "portaudiocpp/Stream.hxx"
#include "portaudiocpp/Exception.hxx"
#include "portaudiocpp/SystemHostApiIterator.hxx"
#include "portaudiocpp/SystemDeviceIterator.hxx"

namespace portaudio
{
    // -----------------------------------------------------------------------------------

    // Static members:
    System *System::instance_ = nullptr;
    int System::initCount_ = 0;
    HostApi **System::hostApis_ = nullptr;
    Device **System::devices_ = nullptr;
    Device *System::nullptrDevice_ = nullptr;

    // -----------------------------------------------------------------------------------

    int System::version()
    {
        return Pa_GetVersion();
    }

    const char *System::versionText()
    {
        return Pa_GetVersionText();
    }

    void System::initialize()
    {
        ++initCount_;

        if (initCount_ == 1)
        {
            // Create singleton:
            assert(instance_ == nullptr);
            instance_ = new System();

            // Initialize the PortAudio system:
            {
                PaError err = Pa_Initialize();

                if (err != paNoError)
                    throw PaException(err);
            }

            // Create and populate device array:
            {
                int numDevices = instance().deviceCount();

                devices_ = new Device*[numDevices];

                for (int i = 0; i < numDevices; ++i)
                    devices_[i] = new Device(i);
            }

            // Create and populate host api array:
            {
                int numHostApis = instance().hostApiCount();

                hostApis_ = new HostApi*[numHostApis];

                for (int i = 0; i < numHostApis; ++i)
                    hostApis_[i] = new HostApi(i);
            }

            // Create nullptr device:
            nullptrDevice_ = new Device(paNoDevice);
        }
    }

    void System::terminate()
    {
        PaError err = paNoError;

        if (initCount_ == 1)
        {
            // Destroy nullptr device:
            delete nullptrDevice_;

            // Destroy host api array:
            {
                if (hostApis_ != nullptr)
                {
                    int numHostApis = instance().hostApiCount();

                    for (int i = 0; i < numHostApis; ++i)
                        delete hostApis_[i];

                    delete[] hostApis_;
                    hostApis_ = nullptr;
                }
            }

            // Destroy device array:
            {
                if (devices_ != nullptr)
                {
                    int numDevices = instance().deviceCount();

                    for (int i = 0; i < numDevices; ++i)
                        delete devices_[i];

                    delete[] devices_;
                    devices_ = nullptr;
                }
            }

            // Terminate the PortAudio system:
            assert(instance_ != nullptr);
            err = Pa_Terminate();

            // Destroy singleton:
            delete instance_;
            instance_ = nullptr;
        }

        if (initCount_ > 0)
            --initCount_;

        if (err != paNoError)
            throw PaException(err);
    }


    System &System::instance()
    {
        assert(exists());
        return *instance_;
    }

    bool System::exists()
    {
        return (instance_ != nullptr);
    }

    // -----------------------------------------------------------------------------------

    System::HostApiIterator System::hostApisBegin()
    {
        System::HostApiIterator tmp;
        tmp.ptr_ = &hostApis_[0]; // begin (first element)
        return tmp;
    }

    System::HostApiIterator System::hostApisEnd()
    {
        int count = hostApiCount();

        System::HostApiIterator tmp;
        tmp.ptr_ = &hostApis_[count]; // end (one past last element)
        return tmp;
    }

    HostApi &System::defaultHostApi()
    {
        PaHostApiIndex defaultHostApi = Pa_GetDefaultHostApi();

        if (defaultHostApi < 0)
            throw PaException(defaultHostApi);

        return *hostApis_[defaultHostApi];
    }

    HostApi &System::hostApiByTypeId(PaHostApiTypeId type)
    {
        PaHostApiIndex index = Pa_HostApiTypeIdToHostApiIndex(type);

        if (index < 0)
            throw PaException(index);

        return *hostApis_[index];
    }

    HostApi &System::hostApiByIndex(PaHostApiIndex index)
    {
        if (index < 0 || index >= hostApiCount())
            throw PaException(paInternalError);

        return *hostApis_[index];
    }

    int System::hostApiCount()
    {
        PaHostApiIndex count = Pa_GetHostApiCount();

        if (count < 0)
            throw PaException(count);

        return count;
    }

    // -----------------------------------------------------------------------------------

    System::DeviceIterator System::devicesBegin()
    {
        DeviceIterator tmp;
        tmp.ptr_ = &devices_[0];

        return tmp;
    }

    System::DeviceIterator System::devicesEnd()
    {
        int count = deviceCount();

        DeviceIterator tmp;
        tmp.ptr_ = &devices_[count];

        return tmp;
    }

    //////
    /// Returns the System's default input Device, or the nullptr Device if none
    /// was available.
    //////
    Device &System::defaultInputDevice()
    {
        PaDeviceIndex index = Pa_GetDefaultInputDevice();
        return deviceByIndex(index);
    }

    //////
    /// Returns the System's default output Device, or the nullptr Device if none
    /// was available.
    //////
    Device &System::defaultOutputDevice()
    {
        PaDeviceIndex index = Pa_GetDefaultOutputDevice();
        return deviceByIndex(index);
    }

    //////
    /// Returns the Device for the given index.
    /// Will throw a paInternalError equivalent PaException if the given index
    /// is out of range.
    //////
    Device &System::deviceByIndex(PaDeviceIndex index)
    {
        if (index < -1 || index >= deviceCount())
        {
            throw PaException(paInternalError);
        }

        if (index == -1)
            return System::instance().nullptrDevice();

        return *devices_[index];
    }

    int System::deviceCount() {
        PaDeviceIndex count = Pa_GetDeviceCount();

        if (count < 0)
            throw PaException(count);

        return count;
    }

    Device &System::nullptrDevice() {
        return *nullptrDevice_;
    }

    // -----------------------------------------------------------------------------------

    void System::sleep(long msec) {
        Pa_Sleep(msec);
    }

    int System::sizeOfSample(PaSampleFormat format) {
        PaError err = Pa_GetSampleSize(format);
        if (err < 0)
        {
            throw PaException(err);
            return 0;
        }

        return err;
    }

} // namespace portaudio
