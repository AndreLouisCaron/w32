// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/mstring.hpp>

namespace w32 {

    mstring::mstring ( const string::box& data )
        : myData(data)
    {
    }

    mstring::mstring ( const string& data )
        : myData(data)
    {
    }

    mstring::mstring ( const wchar_t * data )
        : myData(data)
    {
    }

    mstring::mstring ( const mstring& rhs )
        : myData(rhs.myData)
    {
    }

    mstring::iterator mstring::begin () const
    {
        return (iterator(myData.c_str()));
    }

    mstring::iterator mstring::end () const
    {
        iterator position = begin();
        while ( **position != L'\0' ) {
            ++position;
        }
        return (position);
    }

    void mstring::swap ( mstring& rhs )
    {
        myData.swap(rhs.myData);
    }

    mstring& mstring::operator= ( const mstring& rhs )
    {
        mstring copy(rhs);
        copy.swap(*this);
        return (*this);
    }

    void swap ( mstring& lhs, mstring& rhs )
    {
        lhs.swap(rhs);
    }

    mstring::iterator::iterator ( const wchar_t * position )
        : myPosition(position)
    {
    }

    const wchar_t * mstring::iterator::operator* () const
    {
        return (myPosition);
    }

    mstring::iterator& mstring::iterator::operator++ ()
    {
        for ( ++myPosition; (*myPosition++ != L'\0'); )
            ;
        return (*this);
    }

    mstring::iterator mstring::iterator::operator++ ( int )
    {
        iterator old(*this);
        ++(*this);
        return (old);
    }

    bool mstring::iterator::operator== ( const iterator& other ) const
    {
        return (myPosition == other.myPosition);
    }

    bool mstring::iterator::operator!= ( const iterator& other ) const
    {
        return (myPosition != other.myPosition);
    }

}
