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

#include <w32.shl.ext/ColumnProvider.hpp>

namespace w32 { namespace shl { namespace ext {

    const Column::Alignment Column::Alignment::left ()
    {
        return (LVCFMT_LEFT);
    }

    const Column::Alignment Column::Alignment::right ()
    {
        return (LVCFMT_RIGHT);
    }

    const Column::Alignment Column::Alignment::center ()
    {
        return (LVCFMT_CENTER);
    }

    Column::Alignment::Alignment ( Value value )
        : myValue(value)
    {
    }

    Column::Alignment::Value Column::Alignment::value () const
    {
        return (myValue);
    }

    const Column::Flags Column::Flags::date ()
    {
        return (SHCOLSTATE_TYPE_DATE);
    }

    const Column::Flags Column::Flags::integer ()
    {
        return (SHCOLSTATE_TYPE_INT);
    }

    const Column::Flags Column::Flags::string ()
    {
        return (SHCOLSTATE_TYPE_STR);
    }

    const Column::Flags Column::Flags::slow ()
    {
        return (SHCOLSTATE_SLOW);
    }

    const Column::Flags Column::Flags::onbydefault ()
    {
        return (SHCOLSTATE_ONBYDEFAULT);
    }

    Column::Flags::Flags ()
        : myValue(0)
    {
    }

    Column::Flags::Flags ( Value value )
        : myValue(value)
    {
    }

    Column::Flags::Value Column::Flags::value () const
    {
        return (myValue);
    }

    Column::Flags& Column::Flags::operator|= ( const Flags& other )
    {
        myValue |= other.myValue;
        return (*this);
    }

    Column::Flags Column::Flags::operator| ( const Flags& other ) const
    {
        return (Flags(myValue|other.myValue));
    }

    Column::Flags& Column::Flags::operator&= ( const Flags& other )
    {
        myValue &= other.myValue;
        return (*this);
    }

    Column::Flags Column::Flags::operator& ( const Flags& other ) const
    {
        return (Flags(myValue&other.myValue));
    }

    Column::Column ( ::SHCOLUMNINFO * data )
        : myData(data)
    {
        alignment(Alignment::left());
        flags(Flags::string());
    }

    void Column::identifier ( const com::Guid& class_, ::DWORD index )
    {
        myData->scid.fmtid = class_.value();
        myData->scid.pid = index;
    }

    void Column::type ( const w32::Variant::Type& type )
    {
        myData->vt = type.value();
    }

    void Column::alignment ( const Alignment& alignment )
    {
        myData->fmt &= LVCFMT_JUSTIFYMASK;
        myData->fmt |= alignment.value();
    }

    void Column::width ( uint characters )
    {
        myData->cChars = characters;
    }

    void Column::flags ( const Flags& flags )
    {
        myData->csFlags = flags.value();
    }

    void Column::title ( const string& value )
    {
        const int length = ::_snwprintf(
            myData->wszTitle, MAX_COLUMN_NAME_LEN-1, L"%s", value
            );
        myData->wszTitle[length] = L'\0';
    }

    void Column::description ( const string& value )
    {
        const int length = ::_snwprintf(
            myData->wszDescription, MAX_COLUMN_DESC_LEN-1, L"%s", value
            );
        myData->wszDescription[length] = L'\0';
    }

    EntryData::EntryData ( const ::SHCOLUMNDATA * data )
        : myData(data)
    {
    }

    dword EntryData::flags () const
    {
        return (myData->dwFlags);
    }

    w32::fs::Attributes EntryData::attributes () const
    {
        return (w32::fs::Attributes(myData->dwFileAttributes));
    }

    string EntryData::path () const
    {
        return (myData->wszFile);
    }

    string EntryData::extension () const
    {
        return (myData->pwszExt);
    }

    ::HRESULT __stdcall ColumnProvider::Initialize ( ::LPCSHCOLUMNINIT column )
    {
        try {
            myFolder = column->wszFolder;
        } catch ( const std::bad_alloc& ) {
            return (E_OUTOFMEMORY);
        }
        return (S_OK);
    }

    ::HRESULT __stdcall ColumnProvider::GetColumnInfo (
        ::DWORD index, ::SHCOLUMNINFO * information
        )
    {
            // Columns are numbered starting from 0.
        if ( index >= columns() ) {
            return (S_FALSE);
        }
        
        com::Result result = com::Result::failure();
        
        try {
            Column column(information);
            result = describe(index,column);
        } catch ( const std::bad_alloc& ) {
            return (E_OUTOFMEMORY);
        } catch ( ... ) {
            return (E_FAIL);
        }
        
        return (result.value());
    }

    ::HRESULT __stdcall ColumnProvider::GetItemData (
        ::LPCSHCOLUMNID identifier, ::LPCSHCOLUMNDATA data, ::VARIANT * more
        )
    {
        if ( !identifier || !data || !more ) {
            return (E_POINTER);
        }
        com::Result result = com::Result::failure();
        try {
            EntryData entry(data);
            w32::Variant value; value = *more;
            result = fill(identifier->pid,entry,value);
        } catch ( const std::bad_alloc& ) {
            return (E_OUTOFMEMORY);
        } catch ( ... ) {
            return (E_FAIL);
        }
        
        return (result.value());
    }

} } }
