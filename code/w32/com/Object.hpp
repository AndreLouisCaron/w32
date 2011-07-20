#ifndef _com_Object_hpp__
#define _com_Object_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/com/Allocator.hpp>
#include <w32/com/Guid.hpp>

namespace w32{ namespace com {

        /*!
         * @brief Implements the recurring parts of the IUnknown inteface.
         */
    class Object :
        public ::IUnknown, public NotCopyable
    {
        /* class operators. */
    public:
        inline void * operator new ( std::size_t size )
        {
            return (com::Allocator().acquire(size));
        }

        inline void * operator new
            ( std::size_t size, const std::nothrow_t& ) throw()
        {
            return (com::Allocator().acquire(size, std::nothrow));
        }

        inline void operator delete
            ( void * block, std::size_t ) throw()
        {
            return (com::Allocator().release(block));
        }

        /* data. */
    private:
        volatile ::LONG myReferenceCount;

        /* construction.*/
    public:
        Object ();
        virtual ~Object ();

        /* overrides. */
    public:
        ::ULONG __stdcall AddRef ();
        ::ULONG __stdcall Release ();
        ::HRESULT __stdcall QueryInterface (
            const ::GUID& guid, void ** object
            );

    protected:
        template<typename Interface>
        void * __stdcall query ( const Guid& guid )
        {
            if ( guid == guidof<Interface>() )
            {
                if ( void * object = dynamic_cast<Interface*>(this) ) {
                    AddRef(); return(object);
                }
            }
            return (0);
        }
    };

} }

#endif /* _w32_com_Object_hpp__ */
