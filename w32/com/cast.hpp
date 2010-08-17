#ifndef _w32_com_cast_hpp__
#define _w32_com_cast_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/com/Error.hpp>
#include <w32/com/Guid.hpp>
#include <w32/com/Ptr.hpp>
#include <w32/com/Result.hpp>

namespace w32 { namespace com {

        /*!
         * @brief Wraps clumsy calls to QueryInterface().
         */
    template<typename To, typename From>
    To * cast ( From * object )
    {
        void * alterego = 0;
        if ( object != 0 )
        {
            const Result result = object->QueryInterface(
                guidof<To>().value(), &alterego
                );
            if ( result.bad() ) {
                UNCHECKED_COM_ERROR(IUnknown, QueryInterface, result);
            }
        }
        return (static_cast<To*>(alterego));
    }

        /*!
         * @brief Wraps clumsy calls to QueryInterface().
         */
    template<typename To, typename From>
    Ptr<To> cast ( const Ptr<From>& object )
    {
        return (Ptr<To>( cast<To>(object.value()) ));
    }

} }

#endif /* _w32_com_cast_hpp__ */
