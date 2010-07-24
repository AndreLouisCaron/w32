#ifndef _w32_fs_Search_hpp__
#define _w32_fs_Search_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Object.hpp>
#include <w32/string.hpp>
#include <w32/types.hpp>
#include <w32/fs/Attributes.hpp>
#include <w32/fs/Time.hpp>

namespace w32 { namespace fs {

    class W32_FS_EXPORT Search :
        public Object
    {
        /* nested types. */
    public:
        class Result;

        /* construction. */
    public:
        Search ( const string& pattern, Result& result );

        /* methods. */
    public:
        bool next ( Result& result );
    };

    class W32_FS_EXPORT Search::Result :
        private NotCopyable
    {
        /* nested types. */
    public:
        typedef ::WIN32_FIND_DATAW Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Result ();

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;
        string name () const;
        qword size () const;
        Attributes attributes () const;
        Time creation () const;
        Time access () const;
        Time modification () const;
    };


} }

#endif /* _w32_fs_Search_hpp__ */
