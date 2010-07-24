#ifndef _w32_io_AnonymousPipe_hpp__
#define _w32_io_AnonymousPipe_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/io/Channel.hpp>

namespace w32 { namespace io {

    class W32_IO_EXPORT AnonymousPipe :
        private NotCopyable
    {
        /* nested types. */
    private:
        struct W32_IO_EXPORT Handles
        {
            /* data. */
        public:
            ::HANDLE input;
            ::HANDLE output;

            /* construction. */
        public:
            Handles ();
        };

    public:
        class W32_IO_EXPORT Output :
            public OutputStream
        {
            /* construction. */
        public:
            explicit Output ( const Handles& handles );
        };

        class W32_IO_EXPORT Input :
            public InputStream
        {
            /* construction. */
        public:
            explicit Input ( const Handles& handles );
        };

        /* data. */
    private:
        Handles myHandles;
        Input myInput;
        Output myOutput;

        /* construction. */
    public:
        AnonymousPipe ();

        /* methods. */
    public:
        Input& input () {
            return (myInput);
        }

        Output& output () {
            return (myOutput);
        }

        /* operators. */
    public:
        operator Output& () {
            return (myOutput);
        }

        operator const Output& () const {
            return (myOutput);
        }

        operator Input& () {
            return (myInput);
        }

        operator const Input& () const {
            return (myInput);
        }
    };

} }

#endif /* _w32_io_AnonymousPipe_hpp__ */
