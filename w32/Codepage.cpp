// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/Codepage.hpp>

namespace w32 {

    const Codepage Codepage::ansi ()
    {
        return (CP_ACP);
    }

    const Codepage Codepage::oem ()
    {
        return (CP_OEMCP);
    }

    const Codepage Codepage::utf7 ()
    {
        return (CP_UTF7);
    }

    const Codepage Codepage::utf8()
    {
        return (CP_UTF8);
    }

    Codepage::Codepage ( Value value )
        : myValue(value)
    {
    }

    bool Codepage::valid () const
    {
        return (::IsValidCodePage(myValue) != FALSE);
    }

    Codepage::Value Codepage::value () const
    {
        return (myValue);
    }

    Codepage::operator Value () const
    {
        return (myValue);
    }

    bool Codepage::operator== ( const Codepage& rhs ) const
    {
        return (value() == rhs.value());
    }

    bool Codepage::operator!= ( const Codepage& rhs ) const
    {
        return (value() != rhs.value());
    }

}
