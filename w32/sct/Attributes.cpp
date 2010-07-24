/*!
 * @file w32/sct/Attributes.cpp
 * @author Andre Caron
 */

#include <w32/sct/Attributes.hpp>

namespace w32 {
    namespace sct {

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

    }
}
