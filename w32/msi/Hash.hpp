#ifndef _w32_msi_Hash_hpp__
#define _w32_msi_Hash_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <iosfwd>

namespace w32 { namespace msi {

    class W32_MSI_EXPORT Hash
    {
        /* nested types. */
    public:
        typedef ::MSIFILEHASHINFO Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        explicit Hash ( const char * path );

        /* methods. */
    public:
        Value& value ();
        const Value& value () const;
    };

    std::ostream& operator<< ( std::ostream& out, const Hash& hash );

} }

#endif /* _w32_msi_Hash_hpp__ */
