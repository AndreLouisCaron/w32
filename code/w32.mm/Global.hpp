#ifndef _w32_mm_Global_hpp__
#define _w32_mm_Global_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/Reference.hpp>
#include <w32/types.hpp>

namespace w32 { namespace mm {

    /*!
     * @ingroup w32-mm
     * @brief Legacy memory allocation protocol.
     *
     * You should not use this class unless a given interface requires you
     * to: modern mechanisms, which are also more convenient, exist.
     */
    class Global
    {
        /* nested types. */
    public:
        typedef Reference< ::HGLOBAL > Handle;

        class Lock;

        /* class methods. */
    public:
        static Handle claim ( ::HGLOBAL object );
        static Handle proxy ( ::HGLOBAL object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        Global ( size_t bytes );

        /* methods. */
    public:
        const Handle& handle () const;

            /*!
             * @brief Obtains the current size of the memory block.
             */
        std::size_t size () const;
    };

    class Global::Lock :
        private w32::NotCopyable
    {
        /* data. */
    private:
        void *const myLocation;

        /* construction. */
    public:
        explicit Lock ( Global& object );
        ~Lock ();

        /* methods. */
    public:
        void * location () const;
    };

} }

#endif /* _w32_mm_Global_hpp__ */
