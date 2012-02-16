#ifndef _w32_com_Result_hpp__
#define _w32_com_Result_hpp__

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

namespace w32{ namespace com {

    class Result
    {
        /* nested types. */
    public:
        typedef ::HRESULT Value;

        /* class data. */
    public:
        static const Result success ();
        static const Result failure ();
        static const Result invalid ();
        static const Result false_ ();
        static const Result outofmemory ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        Result ( Value value = 0 )
            : myValue(value)
        {}

        /* methods. */
    public:
        bool good () const {
            return (SUCCEEDED(myValue));
        }

        bool bad () const {
            return (!good());
        }

        Value value () const {
            return (myValue);
        }

        /* operators. */
    public:
        Result& operator= ( ::HRESULT value )
        {
            myValue = value;
            return (*this);
        }

        operator Value () const {
            return (value());
        }

        operator bool () const {
            return (good());
        }

        bool operator! () const {
            return (bad());
        }

        bool operator== ( const Result& other ) const {
            return (myValue == other.myValue);
        }

        bool operator!= ( const Result& other ) const {
            return (myValue != other.myValue);
        }
    };

} }

#endif /* _w32_com_Result_hpp__ */
