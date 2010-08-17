#ifndef _w32_gdi_fonts_hpp__
#define _w32_gdi_fonts_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/gdi/DeviceContext.hpp>

namespace w32 { namespace gdi {

    template<typename Op>
    void fonts ( const DeviceContext& device, Op op )
    {
        struct _
        {
            static int __stdcall enumerate (
                const ::LOGFONTW * lplf, const ::TEXTMETRICW * lptm,
                ::DWORD dwType, ::LPARAM lpData
                )
            {
                    // Process result.
                Op& result = *reinterpret_cast<Op*>(lpData);
                result(lplf->lfFaceName);
                
                    // Keep enumeration going.
                return (TRUE);
            }
        };
        
            // Build description to match.
        ::LOGFONTW attributes;
        ::ZeroMemory(&attributes, sizeof(attributes));
        attributes.lfCharSet = DEFAULT_CHARSET;
        attributes.lfFaceName[0] = L'\0';
        
            // Ask the system to find a match efficiently.
        ::EnumFontFamiliesExW(
            device.handle(), &attributes, &_::enumerate,
            reinterpret_cast<::LPARAM>(&op), 0
            );
    }

} }

#endif /* _w32_gdi_fonts_hpp__ */
