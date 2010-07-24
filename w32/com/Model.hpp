#ifndef _w32_com_Model_hpp__
#define _w32_com_Model_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/com/Object.hpp>

namespace w32{ namespace com {

    template<typename Interface>
    class /*COM_CORE_EXPORT*/ Model :
        virtual public Object, public Interface
    {
        /* overrides. */
    public:
            // Overloaded to avoid ambiguous resolution.
        virtual ::ULONG __stdcall AddRef () {
            return (Object::AddRef());
        }

            // Overloaded to avoid ambiguous resolution.
        virtual ::ULONG __stdcall Release () {
            return (Object::Release());
        }

            // Define casting to implemented interfaces.
        virtual ::HRESULT __stdcall QueryInterface (
            const ::GUID& guid, void ** object
            )
        {
            (*object) = query< Interface >(guid);
            if ( (*object) != 0 ) { return (S_OK); }
            
            return (Object::QueryInterface(guid, object));
        }
    };

} }

#endif /* _w32_com_Model_hpp__ */
