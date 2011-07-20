#ifndef _w32_shl_ext_Extension_hpp__
#define _w32_shl_ext_Extension_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/shl/Path.hpp>

namespace w32 { namespace shl { namespace ext {

        /*!
         * @brief Base class for all extensions: takes care of initialization.
         */
    class Extension :
        public ::IShellExtInit
    {
        /* data. */
    private:
        Path myPath;
        com::Ptr< ::IDataObject > myData;

        /* construction. */
    public:
        virtual ~Extension ();

        /* methods. */
    public:
            /*!
             * @brief Allows access to the data object supplied at
             *   initialization.
             */
        const com::Ptr< ::IDataObject >& data () const;

        /* overrides. */
    public:
        ::HRESULT __stdcall Initialize (
            ::LPCITEMIDLIST path, ::IDataObject * object, ::HKEY
            );
    };

} } }

#endif /* _w32_shl_ext_ContextMenu_hpp__ */
