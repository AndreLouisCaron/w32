#ifndef _w32_gdi_OpenGLContext_hpp__
#define _w32_gdi_OpenGLContext_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/Reference.hpp>

namespace w32 { namespace gdi {

    class DeviceContext;

        /*!
         * @brief Wraps access to an OpenGL context.
         */
    class W32_GDI_EXPORT OpenGLContext
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

    class W32_GDI_EXPORT OpenGLContext::Use :
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
