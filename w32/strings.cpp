// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/strings.hpp>

namespace {

    void abandon ( wchar_t ** strings ) {}
    void destroy ( wchar_t ** strings )
    {
        // Where do we fetch size from? Use custom type?
    }

    w32::Reference< wchar_t** > empty ()
    {
        static wchar_t* data[] = { 0 };
        return (w32::Reference< wchar_t** >(data, &abandon));
    }

}

namespace w32 {

    strings::strings ()
        : myData(::empty())
    {
    }

    const wchar_t ** strings::data () const
    {
        return ((const wchar_t**)(wchar_t**)myData);
    }

    strings::iterator strings::begin () const
    {
        return (iterator(0));
    }

    strings::iterator strings::end () const
    {
        return (iterator(0));
    }

    strings::size_type strings::size () const
    {
        return (0);
    }

    strings::value_type strings::operator[] ( size_type i ) const
    {
        return (((wchar_t**)myData)[i]);
    }

    strings::iterator::iterator ( const wchar_t ** position )
        : myPosition(position)
    {
    }

    const wchar_t * strings::iterator::operator* () const
    {
        return (*myPosition);
    }

    strings::iterator& strings::iterator::operator++ ()
    {
        ++myPosition;
        return (*this);
    }

    strings::iterator strings::iterator::operator++ ( int )
    {
        iterator old(*this);
        ++(*this);
        return (old);
    }

    bool strings::iterator::operator== ( const iterator& other ) const
    {
        return (myPosition == other.myPosition);
    }

    bool strings::iterator::operator!= ( const iterator& other ) const
    {
        return (myPosition != other.myPosition);
    }

}
