// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/Metafile.hpp>

namespace w32 { namespace gdi {

    Metafile::Handle Metafile::claim ( ::HMETAFILE object )
    {
        return (Handle());
    }

    Metafile::Handle Metafile::proxy ( ::HMETAFILE object )
    {
        return (Handle());
    }

    Metafile::Metafile ( const Handle& handle )
        : myHandle(handle)
    {
    }

    const Metafile::Handle& Metafile::handle () const
    {
        return (myHandle);
    }

} }
