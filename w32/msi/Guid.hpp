#ifndef _w32_msi_Guid_hpp__
#define _w32_msi_Guid_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <iosfwd>

namespace w32 { namespace msi {

    class W32_MSI_EXPORT Guid
    {
        /* data. */
    private:
        wchar_t myValue[38+1];

        /* construction. */
    public:
        explicit Guid ( const wchar_t * value );

        /* methods. */
    public:
        string value () const;
    };

    W32_MSI_EXPORT std::wostream&
        operator<< ( std::wostream& out, const Guid& guid );

} }


#endif /* _w32_msi_Guid_hpp__ */
