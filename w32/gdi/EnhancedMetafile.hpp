#ifndef _w32_gdi_EnhancedMetafile_hpp__
#define _w32_gdi_EnhancedMetafile_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Reference.hpp>
#include <w32/gdi/DeviceContext.hpp>

namespace w32 {

    class string;

}

namespace w32 { namespace gdi {

    class Size;

        /*!
         * @brief Macro of GDI drawing commands.
         */
    class W32_GDI_EXPORT EnhancedMetafile
    {
        /* nested types. */
    public:
        typedef Reference< ::HENHMETAFILE > Handle;
        class Compiler;

        /* class methods. */
    public:
        static Handle claim ( ::HENHMETAFILE object );
        static Handle proxy ( ::HENHMETAFILE object );

        static EnhancedMetafile open ( const string& path );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit EnhancedMetafile ( const Handle& handle );
        EnhancedMetafile ( const Size& size, const string& path );
        EnhancedMetafile ( const Size& size, const string& path, const string& description );

        /* methods. */
    public:
        const Handle& handle () const;
    };

        // CreateEnhMetafile() creats a virtual device context; when finished
        // drawing, the call to CloseEnhMetafile() returns a meta file that
        // can be used to play, etc.
        //
        // Find a clean interface for this...
    class W32_GDI_EXPORT EnhancedMetafile::Compiler :
        public DeviceContext
    {
    };

} }

#endif /* _w32_gdi_EnhancedMetafile_hpp__ */
