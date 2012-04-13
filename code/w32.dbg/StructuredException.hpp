#ifndef _w32_dbg_StructuredException_hpp__
#define _w32_dbg_StructuredException_hpp__

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

namespace w32 { namespace dbg {

    /*!
     * @brief Wrapper for Microsoft's structured exception handling (SEH).
     *
     * This helps a lot in debugging some low-level problems. It's role is to
     * translate nitty gritty SEH into short and sweet reports of the problems
     * that occur by translating the SEH errors into C++ exceptions.
     */
    class StructuredException
    {
        /* nested types. */
    public:
        typedef ::_se_translator_function Filter;

        class FilterReplacement;

        /* class data. */
    public:
        /*!
         * @brief Default SEH to C++ exception translation function.
         */
        static const Filter translator ();

        /* construction. */
    public:
        virtual ~StructuredException () {
        }

        /* methods. */
    public:
        /*!
         * @return A textual description of the error.
         */
        virtual const char * what () const = 0;
    };

    /*!
     * @brief Replaces the current SEH to C++ translation function.
     */
    class StructuredException::FilterReplacement :
        private NotCopyable
    {
        /* data. */
    private:
        Filter myPredecessor;

        /* construction. */
    public:
        /*!
         * @brief Changes the SEH to C++ exception filter to @a filter.
         * @param filter Filter function to use as a replacement.
         */
        explicit FilterReplacement ( Filter filter = translator() );

        /*!
         * @brief Restores the previous SEH to C++ exception translator.
         */
        ~FilterReplacement ();
    };

    class UnexpectedException :
        public StructuredException
    {
        /* overrides. */
    public:
        virtual const char * what () const {
            return ("Undocumented structured exception.");
        }
    };

    class AccessViolation :
        public StructuredException
    {
        /* overrides. */
    public:
        virtual const char * what () const {
            return ("Access violation.");
        }
    };

    class DivisionByZero :
        public StructuredException
    {
        /* overrides. */
    public:
        virtual const char * what () const {
            return ("Division by zero.");
        }
    };

} }

#endif /* _w32_dbg_StructuredException_hpp__ */
