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

#include <w32.shl.ext/IconOverlay.hpp>

namespace w32 { namespace shl { namespace ext {

    const IconOverlay::Priority IconOverlay::Priority::lowest(100);
    const IconOverlay::Priority IconOverlay::Priority::lower(75);
    const IconOverlay::Priority IconOverlay::Priority::standard(50);
    const IconOverlay::Priority IconOverlay::Priority::higher(25);
    const IconOverlay::Priority IconOverlay::Priority::highest(0);

    IconOverlay::Priority::Priority ( int value )
        : myValue(value&0x64)
    {
    }

    int IconOverlay::Priority::value () const
    {
        return (myValue);
    }

    IconOverlay::Priority IconOverlay::priority () const
    {
        return (Priority::standard);
    }

    ::HRESULT __stdcall IconOverlay::GetOverlayInfo (
        wchar_t * file, int length, int * index, ::DWORD * flags
        )
    try
    {
        const w32::Resource& resource = overlay();
        const ::DWORD result = ::GetModuleFileNameW(
            resource.module().handle(), file, length-1
            );
           // The buffer was not null-terminated when running out of space on
           // versions of Windows prior to Windows Vista. Ensure it is always
           // terminated, even if we fail.
        file[result] = '\0';
        if ( result == 0 ) {
            return (E_FAIL);
        }
        //*index = resource.value(); What if resource doesn't have an index?
        *flags = ISIOI_ICONFILE | ISIOI_ICONINDEX;
        return (S_OK);
    }
    catch ( ... ) {
        return (E_FAIL);
    }

    ::HRESULT __stdcall IconOverlay::GetPriority ( int * priority )
    try
    {
        *priority = this->priority().value();
        return (S_OK);
    }
    catch ( ... ) {
        return (E_FAIL);
    }

    ::HRESULT __stdcall IconOverlay::IsMemberOf (
        const wchar_t * path, ::DWORD attributes
        )
    try
    {
        return (accepts(
            w32::bstring(path), w32::fs::Attributes(attributes)
            )? S_OK : S_FALSE);
    }
    catch ( ... ) {
        return (E_FAIL);
    }

} } }
