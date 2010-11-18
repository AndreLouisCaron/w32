#ifndef _w32_shl_Stat_hpp__
#define _w32_shl_Stat_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/string.hpp>
#include <w32/types.hpp>
#include <w32/NotCopyable.hpp>

namespace w32 { namespace shl {

    class Storage;

    class W32_SHL_EXPORT Stat
    {
    friend class Storage;

        /* nested types. */
    public:
        typedef ::STATSTG Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Stat ();
        ~Stat ();

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;
        void clear ();

        string name () const;
        qword size () const;
        bool stream () const;
        bool storage () const;
        bool property () const;
        bool bytearray () const;
    };

} }

#endif /* _w32_shl_Stat_hpp__ */
