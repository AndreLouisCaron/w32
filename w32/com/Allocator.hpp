#ifndef _w32_com_Allocator_hpp__
#define _w32_com_Allocator_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/com/Wrapper.hpp>
#include <new>

namespace w32{ namespace com {

    class W32_COM_EXPORT Allocator :
        public Wrapper< ::IMalloc >
    {
        /* nested types. */
    public:
        typedef Wrapper< ::IMalloc >::Ptr Ptr;

        /* construction. */
    public:
        Allocator ();
        Allocator ( const Ptr& backend );

        /* methods. */
    public:
        bool acquired ( const void * block ) const;

        void * acquire ( long bytes );
        void * acquire ( long bytes, const std::nothrow_t& );
        void * reacquire ( const void * block, long bytes );

        template<typename T>
        T * acquire ( long count )
        {
            return (static_cast<T*>(acquire(count*sizeof(T))));
        }

        void release ( const void * block );

        void compact ();

        size_t size ( const void * block ) const;
    };

    inline void * operator new ( std::size_t size, Allocator& allocator )
    {
        return (allocator.acquire(size));
    }

    inline void * operator new (
        std::size_t size, const std::nothrow_t&, Allocator& allocator ) throw()
    {
        return (allocator.acquire(size, std::nothrow));
    }

    inline void operator delete
        ( void * block, std::size_t, Allocator& allocator ) throw()
    {
        return (allocator.release(block));
    }

} }

#endif /* _com_Allocator_hpp__ */
