#ifndef _w32_rgs_Values_hpp__
#define _w32_rgs_Values_hpp__

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
#include <w32.rgs/Key.hpp>

namespace w32 { namespace rgs {

    /*!
     * @ingroup w32-rgs
     * @brief Enumerates a given key's values.
     */
    class Values :
        private NotCopyable
    {
        /* data. */
    private:
        const Key myKey;
        dword myIndex;
        dword myType;
        wchar_t myName[256]; // The maximum name length is 16383...
        long myResult;

        /* construction. */
    public:
        Values ( const Key& key );

        /* methods. */
    public:
        const Key& key () const;

            /*!
             * @brief Returns the name of the value found by @c next().
             * @note This is the empty string unless the last action performed
             *   was a call to @c next() that returned @c true.
             */
        const wchar_t * result () const;

            /*!
             * @brief Reaches the next value.
             * @note This invalides the string returned by @c result(), whether
             *   or not this function succeeds.
             * @return True if another value was found.
             */
        bool next ();
    };

} }

#endif /* _w32_rgs_Values_hpp__ */
