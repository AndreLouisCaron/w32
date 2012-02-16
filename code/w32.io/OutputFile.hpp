#ifndef _w32_io_OutputFile_hpp__
#define _w32_io_OutputFile_hpp__

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
 * @file w32.io/OutputFile.hpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include "__configure__.hpp"
#include <w32/string.hpp>
#include <w32/types.hpp>
#include <w32/NotCopyable.hpp>
#include <w32.io/OutputStream.hpp>

namespace w32 { namespace io {

    /*!
     * @ingroup w32-io
     */
    class OutputFile :
        public OutputStream
    {
        /* nested types. */
    public:
        class Mode
        {
            /* nested types. */
        public:
            typedef ::DWORD Value;

            /* class data. */
        public:
            static const Mode open ();
            static const Mode create ();
            static const Mode replace ();
            static const Mode squash ();
            static const Mode append ();

            /* data. */
        private:
            Value myValue;

            /* construction. */
        private:
            Mode ( Value value );

            /* methods. */
        public:
            Value value () const;
        };

        /* construction. */
    public:
        explicit OutputFile (
            const string& path, const Mode& mode=Mode::squash()
            );
    };

} }

#endif /* _w32_io_OutputFile_hpp__ */
