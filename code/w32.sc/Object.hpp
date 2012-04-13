#ifndef _w32_sc_Object_hpp__
#define _w32_sc_Object_hpp__

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
#include <w32/Reference.hpp>

namespace w32 { namespace sc {

    class Object
    {
        /* nested types. */
    public:
        /*!
         * @brief Holds the system identifier for the service control resource.
         */
        typedef Reference< ::SC_HANDLE > Handle;

        /*!
         * @brief Returns a @c Handle releasing @a object upon its destruction.
         */
        static Handle claim ( ::SC_HANDLE object );

        /*!
         * @brief Returns a @c Handle with a no-op cleanup.
         */
        static Handle proxy ( ::SC_HANDLE object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        /*!
         * @brief Wraps an existing handle.
         */
        explicit Object ( const Handle& handle );
        virtual ~Object ();

        /* methods. */
    public:
        /*!
         * @brief Obtains the SCM resource handle.
         */
        const Handle& handle () const;
    };

} }

#endif /* _w32_sc_Object_hpp__ */
