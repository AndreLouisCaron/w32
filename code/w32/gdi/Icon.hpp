#ifndef _w32_gdi_Icon_hpp__
#define _w32_gdi_Icon_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Reference.hpp>
#include <w32/Resource.hpp>
#include <w32/NotCopyable.hpp>
#include <w32/gdi/Size.hpp>

namespace w32 { namespace gdi {

        /*!
         * @brief Pictogram for an action, state or tool, etc.
         */
    class Icon
    {
        /* nested types. */
    public:
        typedef Reference< ::HICON, void(*)(::HICON) > Handle;

        class Size;

        /* class methods. */
    public:
        static Handle claim ( ::HICON object );
        static Handle proxy ( ::HICON object );

        /* class data. */
    public:
        static const Icon none ();
        static const Icon application ();
        static const Icon asterisk ();
        static const Icon error ();
        static const Icon exclamation ();
        static const Icon hand ();
        static const Icon information ();
        static const Icon question ();
        static const Icon warning ();
        static const Icon winlogo ();

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Icon ( const Handle& handle );
        explicit Icon ( const string& path );
        explicit Icon ( const Resource& resource );
        Icon ( const Resource& resource, const Size& size );
        Icon ( const Resource& resource, const w32::gdi::Size& size );

        /* methods. */
    public:
            /*!
             * @brief Obtains the icon's handle.
             */
        const Handle& handle () const;
    };

    class Icon::Size
    {
        /* nested types. */
    public:
        typedef w32::gdi::Size Value;

        /* class data. */
    public:
        static const Size big ();
        static const Size small ();

        /* data. */
    private:
        Value mySize;

        /* construction. */
    private:
        explicit Size ( const Value& size );

        /* methods. */
    public:
        const Value& value () const;
    };

} }

#endif /* _win32gdi_Icon_hpp__ */
