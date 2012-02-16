#ifndef _w32_com_Wrapper_hpp__
#define _w32_com_Wrapper_hpp__

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
#include <w32.com/Ptr.hpp>

namespace w32{ namespace com {

        /*!
         * @brief Holds a COM handle and defines common methods.
         */
    template<typename T>
    class Wrapper
    {
        /* nested types. */
    public:
        typedef T Binding;
        typedef com::Ptr<Binding> Ptr;

        /* nested types. */
    protected:
        typedef Wrapper<T> Base;

    public:
            /*!
             * @brief Adapts a wrapper class to a new interface.
             *
             * Creates a wrapper object which wraps the same COM object, but
             * with a different (typically extended) interface. This class
             * automagically benefits from an existing wrapper class.
             */
        template<typename U>
        class Rebind
            : public Wrapper<U>
        {
            /* construction. */
        public:
                /*!
                 * @brief Extracts a pointer to the interface.
                 */
            Rebind ( ::IUnknown * object )
                : Wrapper<U>(cast<typename Wrapper::Binding>(object))
            {}

                /*!
                 * @brief Extracts a pointer to the interface.
                 */
            template<typename V>
            Rebind ( const com::Ptr<V>& object )
                : Wrapper<U>(cast<typename Wrapper<U>::Binding>(object))
            {}

                /*!
                 * @brief Extracts a pointer to the interface.
                 */
            template<typename V>
            Rebind ( Wrapper<V>& object )
                : Wrapper<U>(cast<typename Wrapper<U>::Binding>(object.ptr()))
            {}
        };

        /* data. */
    private:
        Ptr myBinding;

        /* construction. */
    public:
            /*!
             * @brief Acquire owneship of handle, no AddRef().
             */
        explicit Wrapper ( Binding * object = 0 )
            : myBinding(object)
        {}

        explicit Wrapper ( const Ptr& object )
            : myBinding(object)
        {}

        /* methods. */
    public:
            /*!
             * @brief Access object, not null-safe.
             */
        Binding& backend () const {
            return (*myBinding);
        }

            /*!
             * @brief Read-only access to the handle.
             */
        const Ptr& ptr () const {
            return (myBinding);
        }
    };

} }

#endif /* _w32_com_Wrapper_hpp__ */
