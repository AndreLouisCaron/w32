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

#include <w32.ts-2/Folder.hpp>
#include <w32.ts-2/Folders.hpp>
#include <w32.ts-2/Service.hpp>
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
