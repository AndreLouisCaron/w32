#ifndef _w32_com_instantiate_hpp__
#define _w32_com_instantiate_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/com/cast.hpp>
#include <w32/com/Error.hpp>
#include <w32/com/Guid.hpp>
#include <w32/com/Ptr.hpp>
#include <w32/com/Result.hpp>

namespace w32 { namespace com {

    inline Ptr< ::IUnknown > instantiate ( const Guid& guid )
    {
        void * instance = 0;
        const Result result = ::CoCreateInstance
            (guid.value(), 0, CLSCTX_ALL, ::IID_IUnknown, &instance);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(void, CoCreateInstance, result);
        }
        return (manage(reinterpret_cast< ::IUnknown* >(instance)));
    }

    template<typename Interface> inline
    Ptr< ::IUnknown > instantiate ( const Guid& guid )
    {
        void * instance = 0;
        const Result result = ::CoCreateInstance(
            guid.value(), 0, CLS_CTX_ALL, guidof<Interface>().value(), &instance
            );
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(void, CoCreateInstance, result);
        }
        return (manage(reinterpret_cast< ::Interface* >(instance)));
    }

} }

#endif /* _w32_com_instantiate_hpp__ */
