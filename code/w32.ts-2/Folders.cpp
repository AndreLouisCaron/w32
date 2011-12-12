// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.ts-2/Folders.hpp>
#include <w32.ts-2/Folder.hpp>

namespace {

    ::ITaskFolderCollection * fetch ( ::ITaskFolder * parent )
    {
        ::ITaskFolderCollection * folders = 0;
        const ::LONG flags = 0;
        const w32::com::Result result = parent->GetFolders(flags,&folders);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskFolder, GetFolders, result);
        }
        return (folders);
    }

}

namespace w32 { namespace ts {

    Folders::Folders ( const Folder& folder )
        : com::Wrapper< ::ITaskFolderCollection >
              ( ::fetch(folder.ptr().value()) )
    {
    }

    long Folders::count () const
    {
        long value = 0;
        const com::Result result = ptr()->get_Count(&value);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskFolderCollection,get_Count,result);
        }
        return (value);
    }

} }
