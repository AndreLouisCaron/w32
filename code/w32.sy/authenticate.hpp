#ifndef _w32_sy_authenticate_hpp__
#define _w32_sy_authenticate_hpp__

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

/*!
 * @file w32.sy/authenticate.hpp
 * @brief Windows account credential validation.
 */

#include "__configure__.hpp"

namespace w32 {

    class string;

}

namespace w32 { namespace sy {

    //! @addtogroup w32-sy
    //! @{

    /*!
     * @brief Validate credentials against the NT LAN Manager (NTLM).
     * @param domain Domain with which the user account is associated.
     * @param username The account's username.
     * @param password The account's password.
     * @return @c true if the credentials can be used to log into the domain,
     *  else @c false.
     *
     * @throws Error There was an unexpected error while validating the
     *  credentials.
     */
    bool authenticate ( const string& domain,
                        const string& username, const string& password );

    //! @}

} }

#endif /* _w32_sy_authenticate_hpp__ */
