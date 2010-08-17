#ifndef _w32_Language_hpp__
#define _w32_Language_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>

namespace w32 {

    class W32_CORE_EXPORT Language
    {
        /* nested types. */
    public:
        typedef ::LANGID Code;

        /* values. */
    public:
        static Language neutral ();
        static Language user ();
        static Language system ();
        static Language en_us ();
        static Language en_ca ();
        static Language fr_ca ();

        /* data. */
    private:
        Code myCode;

        /* construction. */
    private:
            // For internal use only.
        Language ( Code code );
        Language ( word major, word minor );

        /* methods. */
    public:
        Code code () const;

        /* operators. */
    public:
        operator Code () const;
    };

}

#endif /* _w32_Language_hpp__ */
