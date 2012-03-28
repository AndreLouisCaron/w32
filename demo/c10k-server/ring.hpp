#ifndef _ring_hpp__
#define _ring_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/NotCopyable.hpp>
#include <cstddef>

namespace server {

    class ring :
        private w32::NotCopyable
    {
        /* nested types. */
    public:
        typedef unsigned char byte;

        /* data. */
    private:
        byte* myLPtr; byte* myUPtr;
        byte* myGPtr; byte* myPPtr;

        /* construction. */
    public:
        ring ( byte* lptr, byte* uptr );

        /* methods. */
    public:
        std::size_t size () const;
        std::size_t capacity () const;
        bool empty () const;
        bool full () const;

        byte * put ( byte * lower, byte * upper );
        const byte * put ( const byte * lower, const byte * upper );
        byte * get ( byte * lower, byte * upper );
        std::size_t peek ( byte item ) const;

            // Convenient overloads.
        std::size_t put ( byte * data, std::size_t size );
        std::size_t get ( byte * data, std::size_t size );
        std::size_t put ( void * data, std::size_t size );
        std::size_t get ( void * data, std::size_t size );
    };

}

#endif /* _ring_hpp__ */
