#ifndef _w32_mt_CriticalSection_hpp__
#define _w32_mt_CriticalSection_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>

namespace w32 { namespace mt {

    class CriticalSection :
        private NotCopyable
    {
        /* nested types. */
    public:
        typedef ::CRITICAL_SECTION Data;
        class Lock;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        CriticalSection ();
        ~CriticalSection ();

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;
        void enter ();
        bool tryenter ();
        void leave ();
    };

    class CriticalSection::Lock :
        private w32::NotCopyable
    {
        /* data. */
    private:
        CriticalSection& mySection;

        /* construction. */
    public:
        explicit Lock ( CriticalSection& section );
        ~Lock ();
    };


} }

#endif /* _w32_mt_CriticalSection_hpp__ */
