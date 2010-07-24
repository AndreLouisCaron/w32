// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/Language.hpp>

namespace {

        // Fast way to map language IDs to named types.
    template< ::WORD Major, ::WORD Minor >
    struct basic_language : public Language
    {
        basic_language () : Language(MAKELANGID(Major,Minor)) {}
    };

}

namespace w32 {

    Language Language::neutral ()
    {
        return (Language(LANG_NEUTRAL, SUBLANG_NEUTRAL));
    }

    Language Language::user ()
    {
        return (Language(LANG_NEUTRAL, SUBLANG_DEFAULT));
    }

    Language Language::system ()
    {
        return (Language(LANG_NEUTRAL, SUBLANG_SYS_DEFAULT));
    }

    Language Language::en_us ()
    {
        return (Language(LANG_ENGLISH, SUBLANG_ENGLISH_US));
    }

    Language Language::en_ca ()
    {
        return (Language(LANG_ENGLISH, SUBLANG_ENGLISH_CAN));
    }

    Language Language::fr_ca ()
    {
        return (Language(LANG_FRENCH, SUBLANG_FRENCH_CANADIAN));
    }

    Language::Language ( Code code )
        : myCode(code)
    {
    }

    Language::Language ( word major, word minor )
        : myCode(MAKELANGID(major, minor))
    {
    }

    Language::Code Language::code () const
    {
        return (myCode);
    }

    Language::operator Language::Code () const
    {
        return (code());
    }

}
