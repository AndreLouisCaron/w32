/*!
 * @file w32.sy/Attributes.cpp
 * @author Andre Caron
 */

#include <w32.sy/Attributes.hpp>

namespace w32 { namespace sy {

    Attributes::Data& Attributes::get ()
    {
        return (myData);
    }

    const Attributes::Data& Attributes::get () const
    {
        return (myData);
    }

    bool Attributes::inheritable () const
    {
        return (myData.bInheritHandle != FALSE);
    }

    void Attributes::inheritable ( bool value )
    {
        myData.bInheritHandle = ((value)? TRUE : FALSE);
    }

} }
