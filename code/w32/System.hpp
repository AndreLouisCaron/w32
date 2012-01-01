#ifndef _w32_System_hpp__
#define _w32_System_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Architecture.hpp>
#include <w32/types.hpp>

namespace w32 {

    /*!
     * @ingroup w32
     * @brief Information about the operating system's hardware architecture.
     */
    class System
    {
        /* nested types. */
    public:
        typedef ::SYSTEM_INFO Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        System ();

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

        Architecture architecture () const;
        dword pagesize () const;
        dword processors () const;
        dword granularity () const;
    };

}

#endif /* _w32_System_hpp__ */
