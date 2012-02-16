#ifndef _w32_rgs_Access_hpp__
#define _w32_rgs_Access_hpp__

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

namespace w32 { namespace rgs {

    /*!
     * @ingroup w32-rgs
     * @brief Enumerates access types for registry keys.
     * @note The access is given when opening a registry key and only
     *   defines the access the given handle will allow you (i.e. this is
     *   not persistent.
     */
    class Access
    {
        /* nested types. */
    public:
        typedef ::REGSAM Value;

        /* class data. */
    public:
        static const Access list ();
        static const Access get ();
        static const Access set ();
        static const Access create ();
        static const Access read ();
        static const Access write ();
        static const Access all ();

        /* members. */
    private:
        Value myValue;

        /* construction. */
    private:
            // For internal use only.
        Access ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        Access& operator|= ( const Access& other );
        Access operator| ( const Access& other ) const;
        Access& operator&= ( const Access& other );
        Access operator& ( const Access& other ) const;

        operator Value () const;
    };

} }

#endif /* _w32_rgs_Access_hpp__ */
