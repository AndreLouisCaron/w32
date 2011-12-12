// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/MappingMode.hpp>
#include <w32.gdi/DeviceContext.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace gdi {

    const MappingMode MappingMode::text ()
    {
        return (MM_TEXT);
    }

    MappingMode::Selection::Selection (
        const DeviceContext& device, const MappingMode& mode
        )
        : myDevice(device.handle()),
              myPredecessor(::SetMapMode(myDevice, mode.value()))
    {
        if ( myPredecessor == 0 ) {
            UNCHECKED_WIN32C_ERROR(SetMapMode,::GetLastError());
        }
    }

    MappingMode::Selection::~Selection ()
    {
        ::SetMapMode(myDevice,myPredecessor);
    }

    MappingMode MappingMode::of ( const DeviceContext& device )
    {
        const int mode = ::GetMapMode(device.handle());
        if ( mode == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetMapMode, error);
        }
        return (MappingMode(mode));
    }

    MappingMode::MappingMode ( Value value )
        : myValue(value)
    {
    }

    MappingMode::Value MappingMode::value () const
    {
        return (myValue);
    }

} }
