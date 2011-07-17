#ifndef _w32_in_Session_hpp__
#define _w32_in_Session_hpp__

// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Reference.hpp>
#include <w32/string.hpp>

namespace w32 { namespace in {

    class IStream;

    class W32_IN_EXPORT Session
    {
        /* nested types. */
    public:
        typedef Reference< ::HINTERNET > Handle;

        /* class methods. */
    public:
        static const Handle claim ( ::HINTERNET object );
        static const Handle proxy ( ::HINTERNET object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        Session ( const string& agent );

        /* methods. */
    public:
        const Handle& handle () const;

        IStream open ( const string& url );
    };

} }

#endif /* _w32_in_Session_hpp__ */
