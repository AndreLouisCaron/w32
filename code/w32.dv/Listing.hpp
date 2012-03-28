#ifndef _w32_dv_Listing_hpp__
#define _w32_dv_Listing_hpp__

// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "__configure__.hpp"
#include <w32/Error.hpp>
#include <w32/NotCopyable.hpp>
#include <w32/string.hpp>

// The parallel port device interface GUIDs are not always defined by the
// Setup API headers, but it is published in the Setup API documentation.
#ifndef GUID_DEVINTERFACE_PARALLEL
DEFINE_GUID(GUID_DEVINTERFACE_PARALLEL,
  0x97F76EF0L, 0xF883, 0x11D0, 0xAF, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x84, 0x5C);
#endif

#ifndef GUID_DEVINTERFACE_PARCLASS
DEFINE_GUID(GUID_DEVINTERFACE_PARCLASS,
  0x811FC6A5L, 0xF728, 0x11D0, 0xA5, 0x37, 0x00, 0x00, 0xF8, 0x75, 0x3E, 0xD1);
#endif

namespace w32 { namespace dv {

    /*!
     * @brief Enumeration of device classes.
     */
    class Class
    {
        /* nested types. */
    public:
        typedef ::GUID Value;

        /* class methods. */
    public:
        static Class disk ()
        {
            return (GUID_DEVINTERFACE_DISK);
        }

        static Class cdrom ()
        {
            return (GUID_DEVINTERFACE_CDROM);
        }

        static Class partition ()
        {
            return (GUID_DEVINTERFACE_PARTITION);
        }

        static Class tape ()
        {
            return (GUID_DEVINTERFACE_TAPE);
        }

        static Class write_once_disk ()
        {
            return (GUID_DEVINTERFACE_WRITEONCEDISK);
        }

        static Class volume ()
        {
            return (GUID_DEVINTERFACE_VOLUME);
        }

        static Class medium_changer ()
        {
            return (GUID_DEVINTERFACE_MEDIUMCHANGER);
        }

        static Class floppy ()
        {
            return (GUID_DEVINTERFACE_FLOPPY);
        }

        static Class cd_changer ()
        {
            return (GUID_DEVINTERFACE_CDCHANGER);
        }

        static Class storage_port ()
        {
            return (GUID_DEVINTERFACE_STORAGEPORT);
        }

        static Class serial_port ()
        {
            return (GUID_DEVINTERFACE_COMPORT);
        }

        static Class serial_device ()
        {
            return (GUID_DEVINTERFACE_SERENUM_BUS_ENUMERATOR);
        }

        static Class parallel_port ()
        {
            return (GUID_DEVINTERFACE_PARALLEL);
        }

        static Class parallel_device ()
        {
            return (GUID_DEVINTERFACE_PARCLASS);
        }

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        // For internal use only.
        Class ( const Value& value )
            : myValue(value)
        {}

        /* methods. */
    public:
        /*!
         * @brief Obtain the device class GUID.
         */
        operator const Value& () const
        {
            return (myValue);
        }
    };

    /*!
     * @brief Enumerator for all devices of a given class.
     *
     * The class should be used in a loop in the following style:
     * @code
     *  Listing listing(Class::device_class());
     *  for (Entry entry; listing.next(entry);) {
     *    // do something with "entry"...
     *  }
     * @endcode
     */
    class Listing :
        private NotCopyable
    {
        /* nested types. */
    public:
        typedef ::HDEVINFO Handle;

        class Entry;

        /* data. */
    private:
        Handle myHandle;

        ::GUID myType;

        ::SP_DEVICE_INTERFACE_DATA myInterface;
        ::DWORD myIndex;

        /* construction. */
    public:
        /*!
         * @brief Prepare an enumeration context.
         */
        Listing ( const Class& type )
            : myHandle(INVALID_HANDLE_VALUE), myType(type), myIndex(0)
        {
            const ::DWORD flags
                = DIGCF_PRESENT
                | DIGCF_DEVICEINTERFACE;
            myHandle = ::SetupDiGetClassDevs(&myType, 0, 0, flags);
            if (myHandle == INVALID_HANDLE_VALUE)
            {
                const ::DWORD error = ::GetLastError();
                UNCHECKED_WIN32C_ERROR(SetupDiGetClassDevs, error);
            }

            ::ZeroMemory(&myInterface, sizeof(myInterface));
            myInterface.cbSize = sizeof(myInterface);
        }

        /*!
         * @brief Release the enumeration context.
         */
        ~Listing ()
        {
            const ::BOOL result = ::SetupDiDestroyDeviceInfoList(myHandle);
            if (result == FALSE)
            {
                const ::DWORD error = ::GetLastError();
                // ...
            }
        }

        /* methods. */
    public:
        /*!
         * @brief Access the enumeration context handle.
         */
        Handle handle () const;

        /*!
         * @brief Fetch the next entry.
         * @return @c false if there were no more devices left to enumerate,
         *  else @c true.
         * @throws w32::Error An error occured while fetching the next device.
         */
        bool next ( Entry& entry );
    };

    /*!
     * @brief A result object fille for each enumerated device.
     */
    class Listing::Entry :
        private w32::NotCopyable
    {
    friend class Listing;

        /* nested types. */
    public:
        typedef ::SP_DEVINFO_DATA Data;
        typedef ::SP_DEVICE_INTERFACE_DETAIL_DATA_W Details;

        /* data. */
    private:
        mutable Data myData;
        Details * myDetails;

        /* construction. */
    public:
        Entry ()
            : myDetails(0)
        {
            ::ZeroMemory(&myData, sizeof(myData));
            myData.cbSize = sizeof(myData);
        }

        ~Entry ()
        {
            release_details();
        }

        /* methods. */
    private:
        void release_details ()
        {
            if (myDetails) {
                operator delete(myDetails); myDetails = 0;
            }
        }

        void acquire_details ( ::DWORD size )
        {
            // Release the buffer for the previous iteration.
            release_details();

            // Acquire a buffer large enough for the current result.
            myDetails = static_cast<Details*>(operator new(size));
            myDetails->cbSize = sizeof(Details);
        }

        ::DWORD property_size ( ::HDEVINFO listing, ::DWORD property ) const
        {
            ::DWORD size = 0;
            const ::BOOL result = ::SetupDiGetDeviceRegistryPropertyW
                (listing, &myData, property, 0, 0, 0, &size);
            if (result == FALSE)
            {
                const ::DWORD error = ::GetLastError();
                if (error != ERROR_INSUFFICIENT_BUFFER)
                {
                    UNCHECKED_WIN32C_ERROR(
                        SetupDiGetDeviceRegistryProperty, error);
                }
            }
            return (size);
        }

        void property_data ( ::HDEVINFO listing, ::DWORD property,
                             ::LPBYTE data, ::DWORD size ) const
        {
            const ::BOOL result = ::SetupDiGetDeviceRegistryPropertyW
                (listing, &myData, property, 0, data, size, 0);
            if (result == FALSE)
            {
                const ::DWORD error = ::GetLastError();
                UNCHECKED_WIN32C_ERROR(SetupDiGetDeviceRegistryProperty, error);
            }
        }

        string string_property
            ( const Listing& listing, ::DWORD property ) const
        {
            // Query the property size.
            const ::DWORD size = property_size(listing.myHandle, property);

            // Allocate the property buffer.
            ::WCHAR *const data = new ::WCHAR[size/2+1];
            data[size/2] = L'\0';

            // Fetch the property data.
            property_data(listing.myHandle, property,
                          reinterpret_cast<::LPBYTE>(data), size);

            // Wrap the property value.
            return (string(string::box(data)));
        }

    public:
        /*!
         * @brief Get a device path suitable for opening an I/O stream.
         */
        string path () const
        {
            return (string(myDetails->DevicePath));
        }

        /*!
         * @brief Get a device name suitable for display to a user.
         */
        string friendly_name ( const Listing& listing ) const
        {
            return (string_property(listing, SPDRP_FRIENDLYNAME));
        }

        /*!
         * @brief Get a human-readable device description.
         */
        string description ( const Listing& listing ) const
        {
            return (string_property(listing, SPDRP_DEVICEDESC));
        }
    };

    bool Listing::next ( Entry& entry )
    {
        /*const*/ ::BOOL result = ::SetupDiEnumDeviceInterfaces
            (myHandle, 0, &myType, myIndex, &myInterface);
        if (result == 0)
        {
            const ::DWORD error = ::GetLastError();
            if (error == ERROR_NO_MORE_ITEMS) {
                return (false);
            }
            UNCHECKED_WIN32C_ERROR(SetupDiEnumDeviceInterfaces, error);
        }

        // Fetch the details structure size.
        ::DWORD size = 0;
        /*const ::BOOL*/ result = ::SetupDiGetDeviceInterfaceDetailW
            (myHandle, &myInterface, 0, 0, &size, &entry.myData);
        if (result == FALSE)
        {
            const ::DWORD error = ::GetLastError();
            if (error != ERROR_INSUFFICIENT_BUFFER) {
                UNCHECKED_WIN32C_ERROR(SetupDiGetDeviceInterfaceDetail, error);
            }
        }

        // Fetch the details structure data.
        entry.acquire_details(size);
        /*const ::BOOL*/ result = ::SetupDiGetDeviceInterfaceDetailW
            (myHandle, &myInterface, entry.myDetails, size, 0, &entry.myData);
        if (result == FALSE)
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SetupDiGetDeviceInterfaceDetail, error);
        }

        // Got a device, advance position.
        ++myIndex; return (true);
    }

} }

#endif /* _w32_dv_Listing_hpp__ */
