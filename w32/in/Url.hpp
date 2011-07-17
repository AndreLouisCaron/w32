#ifndef _w32_in_url_hpp__
#define _w32_in_url_hpp__

// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/string.hpp>

namespace w32 { namespace in {

    typedef ::INTERNET_PORT Port;

    class W32_IN_EXPORT Url
    {
        /* nested types. */
    public:
        typedef ::URL_COMPONENTS Data;

        /* class methods. */
    public:
        static string encode ( const string& url );
        static string decode ( const string& url );
        static string join ( const string& base, const string& path );

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        explicit Url ( const string& url );

        /* methods. */
    public:
        const Data& data () const;

        string scheme () const;
        string username () const;
        string password () const;

        string host () const;
        Port port () const;
        string path () const;
        string query () const;
    };

} }

#endif /* _w32_in_url_hpp__ */
