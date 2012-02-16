#ifndef _w32_cr_Provider_hpp__
#define _w32_cr_Provider_hpp__

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
 * @file w32.cr/Provider.hpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include "__configure__.hpp"
#include <w32/Reference.hpp>

namespace w32 {

    class string;

}

namespace w32 { namespace cr {

    //! @addtogroup w32-cr
    //! @{

    class Provider
    {
        /* nested types. */
    public:
        typedef Reference< ::HCRYPTPROV > Handle;

        class Hints;
        class Type;

        /* class methods. */
    public:
        static const Handle claim ( ::HCRYPTPROV object );
        static const Handle proxy ( ::HCRYPTPROV object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        Provider ( const Type& type );
        Provider ( const Type& type, const Hints& hints );

        /* methods. */
    public:
        const Handle& handle () const;

        string name () const;
        string container () const;
    };

    class Provider::Type
    {
        /* nested types. */
    public:
        typedef ::DWORD Value;

        /* class methods. */
    public:
        static const Type rsafull ();
        static const Type rsaaes ();
        static const Type rsasig ();
        static const Type rsaschannel ();
        static const Type dss ();
        static const Type dssdh ();
        static const Type dhschannel ();
        static const Type fortezza ();
        static const Type msexchange ();
        static const Type ssl ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Type ( Value value );

        /* operators. */
    public:
        operator Value () const;
    };

    class Provider::Hints
    {
        /* nested types. */
    public:
        typedef ::DWORD Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        Hints ();

        /* methods. */
    public:
        Hints& verifyContext ();
        Hints& newKeySet ();
        Hints& machineKeySet ();
        Hints& deleteKeySet ();
        Hints& silent ();
        Hints& defaultContainerOptional ();

        /* operators. */
    public:
        operator Value () const;
    };

    //! @}

} }

#endif /* _w32_cr_Provider_hpp__ */
