#ifndef _w32_fs_Changes_hpp__
#define _w32_fs_Changes_hpp__

// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
