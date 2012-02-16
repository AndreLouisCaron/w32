#ifndef _w32_in_ftp_hpp__
#define _w32_in_ftp_hpp__

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
#include <w32/NotCopyable.hpp>
#include <w32/string.hpp>
#include <w32/Reference.hpp>
#include <w32.in/Connection.hpp>

namespace w32 { namespace fs {

    class Attributes;
    class Time;

} }

namespace w32 { namespace in {

    class IStream;
    class Session;
    class Url;

} }

namespace w32 { namespace in { namespace ftp {

    /*!
     * @ingroup w32-in
     * @brief
     */
    class Connection :
        public in::Connection
    {
        /* construction. */
    public:
        Connection ( Session& session, const string& url );

        /* methods. */
    public:
        string path () const;
        void path ( const string& path );
        qword size ( const string& file );

        // FtpOpenFile()
        IStream open ( const string& file );

        // FtpGetFile()
        // FtpPutFile()
        void get ( const string& file, const string& path );
        void put ( const string& path, const string& file );

        // FtpRenameFile()
        void move ( const string& from, const string& to );

        // FtpCreateDirectory()
        // FtpRemoveDirectory()
        void mkdir ( const string& name );
        void rmdir ( const string& name );
    };

    // FtpFindFirstFile()
    // InternetFindNextFile()
    // InternetCloseHandle()
    /*!
     * @ingroup w32-in
     * @brief
     */
    class Listing
    {
        /* nested types. */
    public:
        typedef Reference< ::HINTERNET > Handle;

        class Result;

        /* class methods. */
    public:
        static const Handle claim ( ::HINTERNET object );
        static const Handle proxy ( ::HINTERNET object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        Listing ( Connection& connection, Result& result );

        /* methods. */
    public:
        const Handle& handle () const;
        bool next ( Result& result );
    };

    /*!
     * @ingroup w32-in
     * @brief
     */
    class Listing::Result :
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
        fs::Attributes attributes () const;
        fs::Time creation () const;
        fs::Time access () const;
        fs::Time modification () const;
    };

} } }

#endif /* _w32_in_ftp_hpp__ */
