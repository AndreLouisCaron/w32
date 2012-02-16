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

#include <w32.shl/Link.hpp>
#include <w32.shl/Path.hpp>

namespace {

    ::IShellLinkW * create ()
    {
        ::IShellLinkW* value = 0;
        const w32::com::Result result = ::CoCreateInstance(
            CLSID_ShellLink, 0, CLSCTX_INPROC_SERVER,
            IID_IShellLink, (void**)&value
            );
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(none, CoCreateInstance, result);
        }
        return (value);
    }

    // Maximum length for most associated properties.
#if _WIN32_WINNT >= _WIN32_WINNT_WIN2K
    const int MAXIMUM_LENGTH = INFOTIPSIZE;
#else
    const int MAXIMUM_LENGTH = MAX_PATH;
#endif

}

namespace w32 { namespace shl {

    Link::Link ( ::IShellLinkW * object )
        : com::Wrapper< ::IShellLinkW >(object)
    {
    }

    Link::Link ()
        : com::Wrapper< ::IShellLinkW >( ::create() )
    {
    }

    void Link::target ( const Path& path )
    {
        const com::Result result = ptr()->SetIDList(path.backend());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellLink, SetIDList, result);
        }
    }

    Path Link::target () const
    {
        ::ITEMIDLIST * path = 0;
        const com::Result result = ptr()->GetIDList(&path);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellLink, GetPath, result);
        }
        return (Path::box(path));
    }

    void Link::arguments ( const string& value )
    {
        const com::Result result = ptr()->SetArguments(value.data());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellLink, SetArguments, result);
        }
    }

    string Link::arguments () const
    {
        wchar_t buffer[MAXIMUM_LENGTH] = { 0 };
        const com::Result result =
            ptr()->GetArguments(buffer, MAXIMUM_LENGTH);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellLink, GetArguments, result);
        }
        return (buffer);
    }

    void Link::description ( const string& value )
    {
        const com::Result result = ptr()->SetDescription(value.data());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellLink, SetDescription, result);
        }
    }

    string Link::description () const
    {
        wchar_t buffer[MAXIMUM_LENGTH] = { 0 };
        const com::Result result =
            ptr()->GetDescription(buffer, MAXIMUM_LENGTH);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellLink, GetDescription, result);
        }
        return (buffer);
    }

    void Link::icon ( const string& path, int index )
    {
        const com::Result result = ptr()->SetIconLocation(path.data(), index);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellLink, SetIconLocation, result);
        }
    }

    string Link::icon ( int& index ) const
    {
        wchar_t buffer[MAXIMUM_LENGTH] = { 0 };
        const com::Result result =
            ptr()->GetIconLocation(buffer, MAXIMUM_LENGTH, &index);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellLink, GetIconLocation, result);
        }
        return (buffer);
    }

} }
