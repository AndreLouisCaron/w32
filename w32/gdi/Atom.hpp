#ifndef _w32_gdi_Atom_hpp__
#define _w32_gdi_Atom_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/types.hpp>
#include <w32/string.hpp>

namespace w32 { namespace gdi {

        /*!
         * @brief System string-resource identifier.
         */
    class W32_GDI_EXPORT Atom
    {
        /* nested types. */
    public:
        typedef ::ATOM Id;

        /* data. */
    private:
        Id myId;

        /* construction. */
    public:
        explicit Atom ( Id id );
        explicit Atom ( const string& name );

        /* methods. */
    public:
            /*!
             * @brief Get the atom's native value.
             */
        Id id () const;

            /*!
             * @brief Compares the atom with the generic 'bad' value.
             */
        bool bad () const;

            /*!
             * @brief Tests the atom against the generic 'bad' value.
             */
        bool ok () const;

            /*!
             * @brief Obtains the atom's string representation.
             *
             * Do not count on this actually being a string: is is a way for the
             * system to accept names and atoms through the same parameter.
             */
        const wchar_t * raw () const;
    };

} }

#endif /* _w32_gdi_Atom_hpp__ */
