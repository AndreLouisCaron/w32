#ifndef _w32_io_StandardInput_hpp__
#define _w32_io_StandardInput_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/io/InputStream.hpp>

namespace w32 { namespace io {

    class StandardInput :
        public InputStream
    {
        /* nested types. */
    public:
        class Redirection;

        /* construction. */
    public:
        StandardInput ();
    };

    class StandardInput::Redirection :
        private w32::NotCopyable
    {
        /* data. */
    private:
        Handle myPredecessor;

        /* construction. */
    public:
        Redirection ( InputStream& input );
        ~Redirection ();
    };

} }

#endif /* _w32_io_StandardInput_hpp__ */
