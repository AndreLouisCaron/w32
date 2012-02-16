#ifndef _w32_gdi_OpenGLContext_hpp__
#define _w32_gdi_OpenGLContext_hpp__

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

namespace w32 { namespace gdi {

    class DeviceContext;

        /*!
         * @brief Wraps access to an OpenGL context.
         */
    class OpenGLContext
    {
        /* nested types. */
    public:
            /*!
             * @brief Wraps access to a native OpenGL context handle.
             */
        typedef Reference< ::HGLRC > Handle;

        class Use;

        /* class methods. */
    public:
        static Handle claim ( ::HGLRC object );
        static Handle proxy ( ::HGLRC object );

            /*!
             * @brief Obtains the currently selected context.
             * @note If no context is selected, returns a context with a null
             *   handle.
             */
        static OpenGLContext current ();

            /*!
             * @brief Allows two contexts to share display lists.
             *
             * @param lhs 1st display context. May posses display lists.
             * @param rhs 2nd display context. May @e not posses display lists
             *   prior to the time of call.
             *
             * @note Some contexts may not share display lists. However, all
             *   contexts with the same pixel format may share display lists.
             */
        static void share ( const OpenGLContext& lhs, OpenGLContext& rhs );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
            /*!
             * @brief Creates a wrapper for a pre-allocated OpenGL context.
             *
             * @see claim()
             * @see proxy()
             */
        explicit OpenGLContext ( const Handle& handle );

            /*!
             * @brief Creates a new OpenGL context for drawing on @a device.
             */
        explicit OpenGLContext ( const DeviceContext& device );

        /* methods. */
    public:
            /*!
             * @brief Obtains the context's handle.
             */
        const Handle& handle () const ;
    };

    class OpenGLContext::Use :
        private NotCopyable
    {
        /* data. */
    private:
        ::HDC myPreviousDevice;
        ::HGLRC myPreviousContext;

        /* construction. */
    public:
        Use ( DeviceContext& device, OpenGLContext& context );
        ~Use ();
    };

} }

#endif /* _w32_gdi_OpenGLContext_hpp__ */
