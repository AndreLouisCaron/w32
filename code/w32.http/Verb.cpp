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

#include <w32.http/Verb.hpp>
#include <w32.http/Request.hpp>

namespace w32 { namespace http {

    const Verb Verb::unparsed ()
    {
        return (HttpVerbUnparsed);
    }

    const Verb Verb::unknown ()
    {
        return (HttpVerbUnknown);
    }

    const Verb Verb::invalid ()
    {
        return (HttpVerbInvalid);
    }

    const Verb Verb::options ()
    {
        return (HttpVerbOPTIONS);
    }

    const Verb Verb::get ()
    {
        return (HttpVerbGET);
    }

    const Verb Verb::head ()
    {
        return (HttpVerbHEAD);
    }

    const Verb Verb::post ()
    {
        return (HttpVerbPOST);
    }

    const Verb Verb::put ()
    {
        return (HttpVerbPUT);
    }

    const Verb Verb::delete_ ()
    {
        return (HttpVerbDELETE);
    }

    const Verb Verb::trace ()
    {
        return (HttpVerbTRACE);
    }

    const Verb Verb::connect ()
    {
        return (HttpVerbCONNECT);
    }

    const Verb Verb::track ()
    {
        return (HttpVerbTRACK);
    }

    const Verb Verb::move ()
    {
        return (HttpVerbMOVE);
    }

    const Verb Verb::copy ()
    {
        return (HttpVerbCOPY);
    }

    const Verb Verb::propfind ()
    {
        return (HttpVerbPROPFIND);
    }

    const Verb Verb::proppatch ()
    {
        return (HttpVerbPROPPATCH);
    }

    const Verb Verb::mkcol ()
    {
        return (HttpVerbMKCOL);
    }

    const Verb Verb::lock ()
    {
        return (HttpVerbLOCK);
    }

    const Verb Verb::unlock ()
    {
        return (HttpVerbUNLOCK);
    }

    const Verb Verb::search ()
    {
        return (HttpVerbSEARCH);
    }

    const Verb Verb::of ( const Request& request )
    {
        return (request.data().Verb);
    }

    Verb::Verb ( Value value )
        : myValue(value)
    {
    }

    Verb::operator Verb::Value () const
    {
        return (myValue);
    }

    bool Verb::operator== ( const Verb& rhs ) const
    {
        return (myValue == rhs.myValue);
    }

    bool Verb::operator!= ( const Verb& rhs ) const
    {
        return (myValue != rhs.myValue);
    }

} }
