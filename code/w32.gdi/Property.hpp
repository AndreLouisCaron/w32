#ifndef _w32_gdi_Property_hpp__
#define _w32_gdi_Property_hpp__

// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32.gdi/Window.hpp>

namespace w32 { namespace gdi {

        /*!
         * @brief Allows setting named (usally custom) window properties.
         */
    class Property :
        private NotCopyable
    {
        /* data. */
    private:
        Window& myOwner;

        /* construction. */
    public:
        Property ( Window& owner )
            : myOwner(owner)
        {}

        /* methods. */
    public:
            /*!
             * @brief Obtains the name of the window property to get/set.
             */
        virtual const wchar_t * name () const = 0;

            /*!
             * @brief Sets the named property.
             */
        void set ( void * value )
        {
            const ::BOOL result = ::SetPropW(
                myOwner.handle(), name(), value
                );
            if ( result == FALSE ) {
                UNCHECKED_WIN32C_ERROR(SetProp,::GetLastError());
            }
        }

            /*!
             * @brief Returns the current value for the named property.
             *
             * The null return value can either mean that the value is
             * effectivly 0 or that the property does not exist.
             */
        void * get () const {
            return (::GetPropW(myOwner.handle(), name()));
        }

            /*!
             * @brief Retrives, then removes the property value.
             *
             * The null return value can either mean that the value was
             * effectivly 0 or that the property did not exist.
             */
        void * remove () {
            return (::RemovePropW(myOwner.handle(), name()));
        }
    };

} }

#endif /* _w32_gdi_Property_hpp__ */
