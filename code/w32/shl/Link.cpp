// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/shl/Link.hpp>
#include <w32/shl/Path.hpp>

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
