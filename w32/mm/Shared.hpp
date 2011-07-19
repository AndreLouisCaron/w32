#ifndef _w32_mm_Shared_hpp__
#define _w32_mm_Shared_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Object.hpp>
#include <w32/types.hpp>
#include <w32/string.hpp>

namespace w32 { namespace mm {

        /*!
         * @brief Named chunk of memory that can subsequently be mapped onto
         *   other processes' address spaces.
         */
    class Shared :
        virtual public Object
    {
        /* data. */
    private:
        void *const myLocation;

        /* construction. */
    protected:
        explicit Shared ( void * location );

    public:
        explicit Shared ( const string& name );

            /*!
             * @brief Creates a named shared memory block and maps it to the
             *    process' address space.
             *
             * @param name Name of the shared memory object. This must be
             *    communicated to another process for it to map the same memory
             *    into it's address space. This name is case sensitive.
             * @param amount Total number of bytes of memory to allocate.
             *
             * @note The other process(es) that will map the same memory will
             *    obviously inherit a chunk of exactly the same size.
             */
        Shared ( const string& name, size_t amount );

        /* methods. */
    public:
            /*!
             * @brief Obtains the address of the first byte of allocated memory.
             */
        void * location ();

            /*!
             * @brief Obtains the address of the first byte of allocated memory.
             */
        const void * location () const;
    };

} }

#endif /* _w32_mm_Shared_hpp__ */
