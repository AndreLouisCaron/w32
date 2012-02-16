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

#include <w32.gdi/Device.hpp>
#include <w32/string.hpp>
#include <w32/Error.hpp>
#include <functional>
#include <vector>

namespace {

        // Calls container.push_back(argument).
    template<typename Container>
    class BackInserter :
        public std::unary_function< typename Container::value_type, void >
    {
        /* data. */
    private:
        Container& myContainer;

        /* construction. */
    public:
        explicit BackInserter ( Container& container )
            : myContainer(container)
        {}

        /* operators. */
    public:
        result_type operator() ( const argument_type& argument )
        {
            myContainer.push_back(argument);
        }
    };

    template<typename Container>
    BackInserter< Container > back_inserter ( Container& container )
    {
        return (BackInserter< Container >(container));
    }

}

namespace w32 { namespace gdi {

    Device::Device ( const Data& data )
        : myData(data)
    {
    }

    Device::Device ( const string& name )
        : myData()
    {
        myData.cb = sizeof(myData);
        const ::BOOL result = ::EnumDisplayDevicesW
            (name.data(), 0, &myData, 0);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(EnumDisplayDevices, error);
        }
    }

    string Device::name () const
    {
        return (myData.DeviceName);
    }

    string Device::description () const
    {
        return (myData.DeviceString);
    }

    string Device::identifier () const
    {
        return (myData.DeviceID);
    }

    string Device::key () const
    {
        return (myData.DeviceKey);
    }

    bool Device::desktop () const
    {
        return ((myData.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) != 0);
    }

    bool Device::primary () const
    {
        return ((myData.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) != 0);
    }

    bool Device::removable () const
    {
        return ((myData.StateFlags & DISPLAY_DEVICE_REMOVABLE) != 0);
    }

    bool Device::mirroring () const
    {
        return ((myData.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER) != 0);
    }

    std::vector< Device > devices ()
    {
        std::vector< Device > results;
        devices(::back_inserter(results));
        return (results);
    }

} }
