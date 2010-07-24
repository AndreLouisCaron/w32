// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/rgs/Access.hpp>

namespace w32 { namespace rgs {

    const Access Access::list ()
    {
        return (KEY_ENUMERATE_SUB_KEYS);
    }

    const Access Access::get ()
    {
        return (KEY_QUERY_VALUE);
    }

    const Access Access::set ()
    {
        return (KEY_SET_VALUE);
    }

    const Access Access::create ()
    {
        return (KEY_CREATE_SUB_KEY);
    }

    const Access Access::read ()
    {
        return (get()|list());
    }

    const Access Access::write ()
    {
        return (set()|create());
    }

    const Access Access::all ()
    {
        return (KEY_ALL_ACCESS);
    }

    Access::Access ( Value value )
        : myValue(value)
    {
    }

    Access::Value Access::value () const
    {
        return (myValue);
    }

    Access& Access::operator|= ( const Access& other )
    {
        myValue |= other.myValue;
        return (*this);
    }

    Access Access::operator| ( const Access& other ) const
    {
        Access result(*this);
        result |= other;
        return (result);
    }

    Access& Access::operator&= ( const Access& other )
    {
        myValue &= other.myValue;
        return (*this);
    }

    Access Access::operator& ( const Access& other ) const
    {
        Access result(*this);
        result &= other;
        return (result);
    }

    Access::operator Access::Value () const
    {
        return (value());
    }

} }
