#ifndef _w32_Module_hpp__
#define _w32_Module_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/astring.hpp>
#include <w32/Reference.hpp>
#include <w32/string.hpp>

namespace w32 {

    /*!
     * @ingroup w32
     * @brief Loaded executable image: program or library.
     */
    class Module
    {
        /* nested types. */
    public:
        typedef Reference< ::HMODULE, void(*)(::HMODULE) > Handle;

        /* class methods. */
    public:
        static Handle claim ( ::HMODULE object );
        static Handle proxy ( ::HMODULE object );

        static Module load ( const string& path );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Module ( const Handle& handle );
        Module ();
        explicit Module ( const string& name );

        /* methods. */
    public:
        const Handle& handle () const;

        string name () const;
        string path () const;

        void * get ( const astring& symbol ) const;
        template<typename Pointer>
        Pointer get ( const astring& symbol ) const
        {
            Pointer value = 0;
            *reinterpret_cast<void**>(&value) = get(symbol);
            return (value);
        }
    };

}

#endif /* _w32_Module_hpp__ */
