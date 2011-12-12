// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
