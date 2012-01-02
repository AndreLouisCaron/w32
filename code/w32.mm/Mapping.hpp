#ifndef _w32_mm_Mapping_hpp__
#define _w32_mm_Mapping_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Object.hpp>
#include <w32/types.hpp>
#include <w32.fs/File.hpp>

namespace w32 { namespace mm {

    /*!
     * @ingroup w32-mm
     */
    class Mapping :
        public Object
    {
        /* nested types. */
    public:
        class Mode
        {
            /* nested types. */
        public:
            typedef ::DWORD Value;

            /* values. */
        public:
            static Mode i ();
            static Mode o ();

            /* data. */
        private:
            Value myValue;

            /* construction. */
        private:
            Mode ( Value value );

            /* methods. */
        public:
            Value value () const;

            /* operators. */
        public:
            operator Value () const;
        };

        class View;

        /* data. */
    private:
        Mode myMode;

        /* construction. */
    public:
        Mapping ( fs::File& file, Mode mode, qword size = 0 );

        /* methods. */
    public:
        Mode mode () const;
    };

    class Mapping::View
    {
        /* nested types. */
    private:
        typedef Reference< void* > Handle;

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        View ( Mapping& mapping, qword offset=0, dword amount=0 );

        /* methods. */
    public:
        void * location ();

        void flush ( dword amount = 0 );
    };

} }

#endif /* _w32_mm_Mapping_hpp__ */
