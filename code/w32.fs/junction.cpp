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

#include <w32.fs/junction.hpp>
#include <w32.fs/absolute.hpp>
#include <w32.fs/Folder.hpp>
#include <w32.fs/unlink.hpp>
#include <w32/Error.hpp>

/*
 Junctions are actually a special built-in kind of reparse point. Reparse points
 use reparse data buffers and the DeviceIoControl() function. Here are the gory
 details:

 REPARSE_DATA_BUFFER:

 According to Micosoft's documentation on MSDN, the reparse buffer structure
 ressembles this:
 0......8 9.....15 16....23 24....31
 -------- -------- -------- --------
|            Reparse tag            | <- Opcode for DeviceIoControl().
 -------- -------- -------- --------
|   Total length  |   Reserved (0)  | <- Must include full length of buffer.
 -------- -------- -------- --------
|   Link offset   |   Link length   | <- Info about symbolic link.
 -------- -------- -------- --------
|  Target offset  |  Target length  | <- ?
 -------- -------- -------- --------
|               Flags               | <- 0=full path, 1=relative path.
 -------- -------- -------- --------
|       Path buffer (variable       |
|           length) ...             |
 -------- -------- -------- --------
    NOTES: - "link" here refers to what MSDN calls a subtitute name.
           - "target" here is simply shoter than "print name" or whatever.
           - the target part need not used because the handle used in the call
             to DeviceIoControl() refers to the directory we wish to link to.
           - the path buffer should contain the actual values that the link and
             target describe (non-null terminated wide character strings).
           - The offsets refer to the number of bytes past the "target length"
             field.
           - The lengths exclude null character string terminaters.

 The thing is that either Microsoft's documentation on this topic is innaccurate
 or their implementation is bugged, because 1) the paths have to be null
 terminated or DeviceIoControl() refuses the struct as invalidly filled; 2) the
 flags' space in the buffer are occupied by the 4 null bytes mentionned in [1]
 and thus, there is no place to set the SYMLINK_FLAG_RELATIVE constant (and, you
 guessed it, relative paths are not supported; 3) the FSCTL_SET_REPARSE_POINT
 and FSCTL_DELETE_REPARSE_POINT don't have the correct access privilidges and
 and must be redefined.

 REFERENCES:
   http://msdn2.microsoft.com/en-us/library/cc232006.aspx
*/

namespace {

    struct ReparseDataBuffer
    {
        ::DWORD ReparseTag;
        ::WORD  ReparseDataLength;
        ::WORD  Reserved;
        ::WORD  SubstituteNameOffset;
        ::WORD  SubstituteNameLength;
        ::WORD  PrintNameOffset;
        ::WORD  PrintNameLength;
        //DWORD Flags;
        ::WCHAR PathBuffer[MAXIMUM_REPARSE_DATA_BUFFER_SIZE-16];

        explicit ReparseDataBuffer ( const w32::string& target )
        {
            const ::WORD bytes =
                static_cast< ::WORD >(target.length() * sizeof(::WCHAR));
            ReparseTag           = IO_REPARSE_TAG_MOUNT_POINT;
            ReparseDataLength    = 12 + bytes;
            Reserved             = 0;
            SubstituteNameOffset = 0;
            SubstituteNameLength = bytes;
            PrintNameOffset      = bytes + 2;
            PrintNameLength      = 0;
            /*SymbolicLinkReparseBuffer.Flags =
              SECRET_SYMLINK_FLAG_ABSOLUTE;*/ // Lost this value?
            ::wcscpy(PathBuffer,target.c_str());
        }

        ::WORD size () const {
            return (8 + ReparseDataLength);
        }
    };

}

namespace w32 { namespace fs {

    void junction ( string target, const string& alias )
    {
            // Reparse-points must *absolutely* use full paths.
        target = absolute(target);
        
            // Create an empty folder.
        Folder::create(alias);
        try
        {
                // Get the new folder's handle.
            ReparsePoint folder(alias);
            
                // Morph the folder into a reparse point.
            ::ReparseDataBuffer buffer(target);
            ::DWORD written = 0;
            const ::BOOL result = ::DeviceIoControl(
                folder.handle(), FSCTL_SET_REPARSE_POINT,
                &buffer, buffer.size(), 0, 0, &written, 0
                );
            if ( result == FALSE )
            {
                const ::DWORD error = ::GetLastError();
                UNCHECKED_WIN32C_ERROR(DeviceIoControl, error);
            }
        }
            // Remove the empty directory.
        catch ( ... ) {
            unlink(alias); throw;
        }
    }

} }
