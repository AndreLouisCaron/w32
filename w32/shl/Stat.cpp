// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/shl/Stat.hpp>
#include <w32/string.hpp>

namespace w32 { namespace shl {

    Stat::Stat ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
    }

    Stat::Stat ( const Stat& other )
        : myName(other.myName)
    {
        ::CopyMemory(&myData, &other.myData, sizeof(myData));
    }

    Stat::Data& Stat::data ()
    {
        return (myData);
    }

    const Stat::Data& Stat::data () const
    {
        return (myData);
    }

    string Stat::name () const
    {
        return (myName);
    }

    qword Stat::size () const
    {
        return (myData.cbSize.QuadPart);
    }

    bool Stat::storage () const
    {
        return (myData.type == STGTY_STORAGE);
    }

    bool Stat::stream () const
    {
        return (myData.type == STGTY_STREAM);
    }

    bool Stat::property () const
    {
        return (myData.type == STGTY_PROPERTY);
    }

    bool Stat::bytearray () const
    {
        return (myData.type == STGTY_LOCKBYTES);
    }

} }
