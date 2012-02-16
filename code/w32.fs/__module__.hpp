#ifndef _w32_fs_hpp__
#define _w32_fs_hpp__

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

#include "__configure__.hpp"

namespace w32 {
    namespace fs {}
}
/*!
 * @defgroup w32-fs Filesystem services.
 *
 * Services used to inspect and manipulate drives, folders and files.  This
 * group does not provide facilities for input and output to files and devices.
 */

#include <w32.fs/absolute.hpp>
#include <w32.fs/Attributes.hpp>
#include <w32.fs/Changes.hpp>
#include <w32.fs/copy.hpp>
#include <w32.fs/drives.hpp>
#include <w32.fs/File.hpp>
#include <w32.fs/Folder.hpp>
#include <w32.fs/hardlink.hpp>
#include <w32.fs/junction.hpp>
#include <w32.fs/move.hpp>
#include <w32.fs/Search.hpp>
#include <w32.fs/symlink.hpp>
#include <w32.fs/Time.hpp>
#include <w32.fs/unlink.hpp>

#endif /* _w32_fs_hpp__ */
