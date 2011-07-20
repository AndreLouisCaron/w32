// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/Device.hpp>
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
