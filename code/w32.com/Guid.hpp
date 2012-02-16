#ifndef _w32_com_Guid_hpp__
#define _w32_com_Guid_hpp__

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
#include <w32/types.hpp>
#include <iosfwd>

namespace w32{ namespace com {

    class Guid
    {
        /* nested types. */
    public:
        typedef ::GUID Value;

        class String;

        /* class data. */
    public:
        static const Guid zero ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        Guid (
            dword a, word b, word c,
            byte d, byte e, byte f, byte g,
            byte h, byte i, byte j, byte k
            );

        Guid ( const Guid& other = zero() );

        Guid ( const Value& value );

        /* methods. */
    public:
        Value& value ();
        const Value& value () const;

        /* operators. */
    public:
        Guid& operator= ( const Guid& other );

        operator const Value& () const;
        bool operator== ( const Guid& other ) const;
        bool operator!= ( const Guid& other ) const;
    };

    std::wostream& operator<<
        ( std::wostream& out, const Guid& guid );

    std::wistream& operator>>
        ( std::wistream& in, Guid& guid );

    class Guid::String
    {
        /* data. */
    private:
        wchar_t myValue[39];

        /* construction. */
    public:
        String ( const Guid& guid );

        /* methods. */
    public:
        const wchar_t * value () const;
    };

    std::wostream& operator<<
        ( std::wostream& out, const Guid::String& guid );

        /*!
         * @brief Returns the identifier for a given class/interface.
         *
         * Specialize this function for any class or interface you write or
         * wrap (it is not pre-defined for all classes).
         */
    template<typename Interface> Guid guidof ();

    template<> inline Guid guidof< ::IUnknown > () { return (::IID_IUnknown); }

} }

#endif /* _w32_com_Guid_hpp__ */
