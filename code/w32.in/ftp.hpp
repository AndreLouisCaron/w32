#ifndef _w32_in_ftp_hpp__
#define _w32_in_ftp_hpp__

// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
