#ifndef _w32_rgs_Value_hpp__
#define _w32_rgs_Value_hpp__

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
#include <w32/string.hpp>
#include <w32/types.hpp>
#include <w32.rgs/Key.hpp>
#include <w32.rgs/Type.hpp>

namespace w32 { namespace rgs {

    /*!
     * @ingroup w32-rgs
     * @brief Allows manipulation of registry key values.
     *
     * @todo Only handles strings and dwords for now.
     */
    class Value
    {
        /* data. */
    private:
        const Key myKey;
        const string myName;

        /* construction. */
    public:
            /*!
             * @Opens the value under @c key named @name.
             *
             * The key does not need to exist before hand. For queries, an error
             * is raised when querying the value's type or it's data. To write,
             * the registry creates the value on the fly. Also, the type is
             * changed to whatever you set it with no matter what it was before
             * hand.
             */
        Value ( const Key& key, const string& name );
        Value (
            const Key& key, const string& name, const string& value
            );

        /* operators. */
    public:
        const Key& key () const;
        const string& name () const;
            /*!
             * @brief Returns the type of value.
             */
        Type type () const;
        Value& operator= ( const string& value );
        operator const string () const;
        Value& operator= ( const dword& data );
    };

} }

#endif /* _w32_rgs_Value_hpp__ */
