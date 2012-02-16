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

#include <w32/Language.hpp>

namespace {

        // Fast way to map language IDs to named types.
    template< ::WORD Major, ::WORD Minor >
    struct basic_language : public Language
    {
        basic_language () : Language(MAKELANGID(Major,Minor)) {}
    };

}

namespace w32 {

    Language Language::neutral ()
    {
        return (Language(LANG_NEUTRAL, SUBLANG_NEUTRAL));
    }

    Language Language::user ()
    {
        return (Language(LANG_NEUTRAL, SUBLANG_DEFAULT));
    }

    Language Language::system ()
    {
        return (Language(LANG_NEUTRAL, SUBLANG_SYS_DEFAULT));
    }

    Language Language::en_us ()
    {
        return (Language(LANG_ENGLISH, SUBLANG_ENGLISH_US));
    }

    Language Language::en_ca ()
    {
        return (Language(LANG_ENGLISH, SUBLANG_ENGLISH_CAN));
    }

    Language Language::fr_ca ()
    {
        return (Language(LANG_FRENCH, SUBLANG_FRENCH_CANADIAN));
    }

    Language::Language ( Code code )
        : myCode(code)
    {
    }

    Language::Language ( word major, word minor )
        : myCode(MAKELANGID(major, minor))
    {
    }

    Language::Code Language::code () const
    {
        return (myCode);
    }

    Language::operator Language::Code () const
    {
        return (code());
    }

}
