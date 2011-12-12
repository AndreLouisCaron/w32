// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/TextMetrics.hpp>
#include <w32.gdi/DeviceContext.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace gdi {

    TextMetrics::TextMetrics ( const DeviceContext& device )
    {
        const ::BOOL result = ::GetTextMetricsW(device.handle(), &myData);
        if ( result == FALSE ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetTextMetrics, error);
        }
    }

    TextMetrics::Data& TextMetrics::data ()
    {
        return (myData);
    }

    const TextMetrics::Data& TextMetrics::data () const
    {
        return (myData);
    }

    long TextMetrics::height () const
    {
        return (myData.tmHeight);
    }

} }
