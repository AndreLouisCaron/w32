#ifndef _w32_in_http_hpp__
#define _w32_in_http_hpp__

// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

// See http://msdn.microsoft.com/en-us/library/cc185684(VS.85).aspx for use of
// asynchronous facilities, enabling single-threaded non-blocking UI.

namespace w32 { namespace in { namespace http {

    // Sending a request:
    //   > HttpOpenRequest()
    //   > HttpAddRequestHeaders()
    //   > HttpSendRequest()
    //
    // Receiving a response:
    //   < HttpQueryInfo()
    //   < InternetReadFile()
    //
    // InternetCloseHandle()
    //
    // Once all the response has been read, the request object may be re-used.
    // In particular, set the INTERNET_FLAG_KEEP_CONNECTION flag in
    // HttpOpenRequest() to enable HTTP keep alive for multiple downloads.
    /*!
     * @ingroup w32-in
     * @brief
     */
    class Request
    {
    };

} } }

#endif /* _w32_in_http_hpp__ */
