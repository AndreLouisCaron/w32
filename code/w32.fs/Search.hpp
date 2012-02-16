#ifndef _w32_fs_Search_hpp__
#define _w32_fs_Search_hpp__

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
#include <w32/Object.hpp>
#include <w32/string.hpp>
#include <w32/types.hpp>
#include <w32.fs/Attributes.hpp>
#include <w32.fs/Time.hpp>

namespace w32 { namespace fs {

    /*!
     * @ingroup w32-fs
     * @brief Folder listing, possibly filtered by name (using wildcards).
     */
    class Search :
        public Object
    {
        /* nested types. */
    public:
        class Result;

        /* class methods. */
    public:
        static const Handle claim ( ::HANDLE object );

        /* construction. */
    public:
        Search ( const string& pattern, Result& result );

        /* methods. */
    public:
        bool next ( Result& result );
    };

    class Search::Result :
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
