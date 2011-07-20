#ifndef _w32_shl_Dropping_hpp__
#define _w32_shl_Dropping_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/shl/Data.hpp>

namespace w32 { namespace shl {

    class Dropping :
        private NotCopyable
    {
        /* data. */
    private:
        ::HDROP myDrop;
        ::DWORD myIndex;
        ::STGMEDIUM myMedium;

        /* construction. */
    public:
        explicit Dropping ( const Data& data );
        ~Dropping ();

        /* methods. */
    public:
        uint count () const;

        /* operators. */
    public:
        const string operator[] ( w32::dword index ) const;
    };

} }

#endif /* _w32_shl__Dropping_hpp__ */
