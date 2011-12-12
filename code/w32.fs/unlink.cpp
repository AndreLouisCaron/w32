// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.fs/unlink.hpp>
#include <w32.fs/Attributes.hpp>
#include <w32.fs/File.hpp>
#include <w32.fs/Folder.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace fs {

    void unlink ( const string& path )
    {
            // Check what kind of file system entry we are dealing with. This
            // also covers non-existing entries.
        const Attributes attributes(path);
        if ( attributes.invalid() ) {
            return;
        }
        
            // Handle junctions properly.
            // TODO: check if this covers real mount points?
        if ( attributes.reparsepoint() )
        {
                // A junction is a folder with a special attribute.
            Folder folder(path);
            
                // Remove the special attribute.
            ::REPARSE_GUID_DATA_BUFFER reparsedata = { 0 };
            reparsedata.ReparseTag = IO_REPARSE_TAG_MOUNT_POINT;
            ::DWORD bytes = 0;
            ::BOOL result = ::DeviceIoControl(
                folder.handle(), FSCTL_DELETE_REPARSE_POINT, &reparsedata,
                REPARSE_GUID_DATA_BUFFER_HEADER_SIZE, NULL, 0, &bytes, 0
                );
            if ( result == FALSE ) {
                UNCHECKED_WIN32C_ERROR(DeviceIoControl,::GetLastError());
            }
            
                // Delete the folder itself.
            Folder::remove(path); return;
        }
        
            // Handle directories properly.
        if ( attributes.folder() )
        {
            Folder::remove(path); return;
        }
        
            // Under all other circumstances, this should do the right thing.
        File::remove(path);
    }

} }
