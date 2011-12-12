// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.shl/Dropping.hpp>

namespace w32 { namespace shl {

    Dropping::Dropping ( const Data& data )
        : myDrop(0), myIndex(0)
    {
            // Ask for the list of files.
        ::FORMATETC format;
        format.cfFormat = CF_HDROP;
        format.ptd = 0;
        format.dwAspect = DVASPECT_CONTENT;
        format.lindex = -1;
        format.tymed = TYMED_HGLOBAL;
        
            // Obtain the medium to the dropped data.
        myMedium.tymed = TYMED_HGLOBAL;
        myMedium.hGlobal = 0;
        myMedium.pUnkForRelease = 0;
        data.get(format,myMedium);
        
            // Gain access to the description of the dropped data.
        myDrop = reinterpret_cast<::HDROP>(::GlobalLock(myMedium.hGlobal));
    }

    Dropping::~Dropping ()
    {
        ::GlobalUnlock(myMedium.hGlobal);
        ::ReleaseStgMedium(&myMedium);
    }

    uint Dropping::count () const
    {
        return (::DragQueryFileW(myDrop,0xFFFFFFFF,0,0));
    }

    const string Dropping::operator[] ( w32::dword index ) const
    {
        const w32::uint length = ::DragQueryFileW(myDrop,index,0,0);
        string result(length+1,'\0');
        const w32::uint written = ::DragQueryFileW(
            myDrop, index, const_cast<wchar_t*>(result.data()), length+1
            );
        result.resize(length);
        return (result);
    }

} }
