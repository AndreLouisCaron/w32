// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/ts-2/Folder.hpp>
#include <w32/ts-2/Folders.hpp>
#include <w32/ts-2/Service.hpp>
#include <w32/Variant.hpp>

namespace {

    ::ITaskFolder * create ( ::ITaskFolder * parent, ::BSTR path )
    {
        w32::Variant security;
        ::ITaskFolder * folder = 0;
        const w32::com::Result result = parent->CreateFolder(
            path, security.value(), &folder
            );
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskFolder, CreateFolder, result);
        }
        return (folder);
    }

    ::ITaskFolder * open ( ::ITaskService * service, ::BSTR path )
    {
        ::ITaskFolder * folder = 0;
        const w32::com::Result result = service->GetFolder(path,&folder);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskService, GetFolder, result);
        }
        return (folder);
    }

    ::ITaskFolder * open ( ::ITaskFolder * parent, ::BSTR path )
    {
        ::ITaskFolder * folder = 0;
        const w32::com::Result result = parent->GetFolder(path, &folder);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskFolder, GetFolder, result);
        }
        return (folder);
    }

    ::ITaskFolder * open ( ::ITaskFolderCollection * list, long name )
    {
        ::ITaskFolder * folder = 0;
        const w32::Variant index(name);
        const w32::com::Result result = list->get_Item(index.value(),&folder);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskFolderCollection, get_Item, result);
        }
        return (folder);
    }

    ::ITaskFolder * open ( ::ITaskFolderCollection * list, ::BSTR name )
    {
        ::ITaskFolder * folder = 0;
        const w32::Variant index(name);
        const w32::com::Result result = list->get_Item(index.value(), &folder);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskFolderCollection, get_Item, result);
        }
        return (folder);
    }

        // ::BSTR is non-const, even for read-only access!
    wchar_t root[] = L"\\";

}

namespace w32 { namespace ts {

    Folder Folder::create ( Folder& parent, const bstring& name )
    {
        return (Folder( ::create(parent.ptr().value(), name.value()) ));
    }

    Folder::Folder ( ::ITaskFolder * instance )
        : com::Wrapper< ::ITaskFolder >(instance)
    {
    }

    Folder::Folder ( Service& service )
        : com::Wrapper< ::ITaskFolder >
              ( ::open(service.ptr().value(), bstring(L"\\").value()) )
    {
    }

    Folder::Folder ( Service& service, const bstring& path )
        : com::Wrapper< ::ITaskFolder >
              ( ::open(service.ptr().value(), path.value()) )
    {
    }

    Folder::Folder ( Folder& parent, const bstring& path )
        : com::Wrapper< ::ITaskFolder >
              ( ::open(parent.ptr().value(), path.value()) )
    {
    }

    Folder::Folder ( const Folders& list, long index )
        : com::Wrapper< ::ITaskFolder >
              ( ::open(list.ptr().value(), index) )
    {
    }

    Folder::Folder ( const Folders& list, const bstring& name )
        : com::Wrapper<::ITaskFolder>
              ( ::open(list.ptr().value(), name.value()) )
    {
    }

    bstring Folder::name () const
    {
        ::BSTR value = 0;
        const com::Result result = ptr()->get_Name(&value);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskFolder,get_Name,result);
        }
        return (bstring(value));
    }

    bstring Folder::path () const
    {
        ::BSTR value = 0;
        const com::Result result = ptr()->get_Path(&value);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskFolder, get_Path, result);
        }
        return (bstring(value));
    }

} }
