#ifndef _w32_Object_hpp__
#define _w32_Object_hpp__

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
#include <w32/Reference.hpp>

namespace w32 {

    /*!
     * @ingroup w32
     * @brief Base class for kernel objects.
     */
    class Object
    {
        /* nested types. */
    public:
        /*!
         * @brief Shared reference to the native system handle.
         */
        typedef Reference< ::HANDLE > Handle;

        /*!
         * @brief Returns a @c Handle releasing @a object upon its destruction.
         */
        static Handle claim ( ::HANDLE object );

        /*!
         * @brief Returns a @c Handle with a no-op cleanup.
         */
        static Handle proxy ( ::HANDLE object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    protected:
        explicit Object ( const Handle& handle );

        /*!
         * This function is never, ever invoked because there is no other means
         * than the parametric constructor to assign the object a handle.
         * However, it is required because of virtual inheritance in some
         * kernel objects.  This seems to be a limitation of the language
         * ensuring a default constructor to classes such as @c w32::Waitable.
         */
        Object ();

    public:
        /*!
         * @brief Releases the kernel object.
         */
        virtual ~Object ();

        /* methods. */
    public:
        /*!
         * @return The system handle for the kernel object.
         */
        const Handle& handle () const;

        /*!
         * @brief Force premature release of the kernel object.
         *
         * This method should really be avoided whenever possible, as using it
         * may break class invariants.
         */
        void destroy ();
    };

}

#endif /* _w32_Object_hpp__ */
