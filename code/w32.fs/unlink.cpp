// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
