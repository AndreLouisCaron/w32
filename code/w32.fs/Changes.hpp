#ifndef _w32_fs_Changes_hpp__
#define _w32_fs_Changes_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Reference.hpp>
#include <w32/string.hpp>
#include <w32/Waitable.hpp>

namespace w32 { namespace fs {

    /*!
     * @ingroup w32-fs
     * @brief Registration for notification of changes on the file-system.
     */
    class Changes :
        public Object
    {
        /* nested types. */
    public:
        class Filter;

        /* construction. */
    public:
        explicit Changes
            ( const string& path, const Filter& filter, bool recursive=false );
        Changes ( const Handle& handle );

        /* methods. */
    public:
        void next () const;

        operator Waitable () const;
    };

    class Changes::Filter
    {
        /* nested types. */
    public:
        typedef dword Value;

        /* class data. */
    public:
        static const Filter filename ();
        static const Filter foldername ();
        static const Filter attributes ();
        static const Filter size ();
        static const Filter lastwrite ();
        static const Filter security ();
        static const Filter all ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
            // For internal use only.
        Filter ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        Filter& operator|= ( const Filter& other );
        Filter operator| ( const Filter& other ) const;
        Filter& operator&= ( const Filter& other );
        Filter operator& ( const Filter& other ) const;
    };

} }

#endif /* _w32_fs_Changes_hpp__ */
