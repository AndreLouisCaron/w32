#ifndef _w32_io_OutputFile_hpp__
#define _w32_io_OutputFile_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/string.hpp>
#include <w32/types.hpp>
#include <w32/NotCopyable.hpp>
#include <w32/io/OutputStream.hpp>

namespace w32 { namespace io {

        /*!
         */
    class W32_IO_EXPORT OutputFile :
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
            const string& path, const Mode& mode=Mode::replace()
            );
    };

} }

#endif /* _w32_io_OutputFile_hpp__ */
