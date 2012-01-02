#ifndef _w32_mm_Aligned_hpp__
#define _w32_mm_Aligned_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/types.hpp>
#include <w32.mm/Allocator.hpp>

namespace w32 { namespace mm {

    /*!
     * @ingroup w32-mm
     */
    class Aligned :
        public Allocator
    {
        /* data. */
    private:
        size_t myAlignment;

        /* class methods. */
    public:
        static bool supports ( size_t alignment );

        /* construction. */
    public:
        Aligned ( size_t alignment );

        /* methods. */
    public:
        size_t alignment () const {
            return (myAlignment);
        }

        /* overrides. */
    public:
        virtual void * acquire ( size_t amount );
        virtual void release ( void * start, size_t );
    };

} }

#endif /* _w32_mm_Aligned_hpp__ */
