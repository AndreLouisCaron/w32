#ifndef _w32_shl_Binding_hpp__
#define _w32_shl_Binding_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>
#include <w32.com/Wrapper.hpp>

namespace w32 { namespace shl {

    class Binding :
        public com::Wrapper< ::IBindCtx >
    {
        /* nested types. */
    public:
        class Options;

        /* construction. */
    public:
        Binding ();

        /* methods. */
    public:
        Options options () const;
        void options ( const Options& options );
    };

    class Binding::Options
    {
        /* nested types. */
    public:
        typedef ::BIND_OPTS Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Options ();

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

        void access ( dword access );
    };
} }

#endif /* _w32_shl_Binding_hpp__ */
