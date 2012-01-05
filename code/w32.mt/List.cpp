// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.mt/List.hpp>

namespace w32 { namespace mt {

    List::List ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
        ::InitializeSListHead(&myData);
    }

    List::~List ()
    {
        clear();
    }

    List::Data& List::data ()
    {
        return (myData);
    }

    const List::Data& List::data () const
    {
        return (myData);
    }

    List::size_type List::size () const
    {
        return (::QueryDepthSList(&const_cast<Data&>(myData)));
    }

    void List::push ( Item * item )
    {
        ::InterlockedPushEntrySList(&myData, item);
    }

    List::Item * List::pop ()
    {
        return (::InterlockedPopEntrySList(&myData));
    }

    List::Item * List::clear ()
    {
        return (::InterlockedFlushSList(&myData));
    }

    List::iterator List::begin ()
    {
        return (iterator(::RtlFirstEntrySList(&myData)));
    }

    List::iterator List::end ()
    {
        iterator position = begin();
        while ( *position != 0 ) {
            ++position;
        }
        return (position);
    }

    List::const_iterator List::begin () const
    {
        return (const_iterator(::RtlFirstEntrySList(&myData)));
    }

    List::const_iterator List::end () const
    {
        const_iterator position = begin();
        while ( *position != 0 ) {
            ++position;
        }
        return (position);
    }

    List::iterator::iterator ( List::Item * position )
        : myPosition(position)
    {
    }

    List::Item * List::iterator::operator* () const
    {
        return (myPosition);
    }

    List::iterator& List::iterator::operator++ ()
    {
        myPosition = myPosition->Next;
        return (*this);
    }

    List::iterator List::iterator::operator++ ( int )
    {
        iterator old(*this);
        ++(*this);
        return (old);
    }

    bool List::iterator::operator== ( const iterator& other ) const
    {
        return (myPosition == other.myPosition);
    }

    bool List::iterator::operator!= ( const iterator& other ) const
    {
        return (myPosition != other.myPosition);
    }

    List::const_iterator::const_iterator ( const List::Item * position )
        : myPosition(position)
    {
    }

    List::const_iterator::const_iterator ( const List::iterator& position )
        : myPosition(*position)
    {
    }

    const List::Item * List::const_iterator::operator* () const
    {
        return (myPosition);
    }

    List::const_iterator& List::const_iterator::operator++ ()
    {
        myPosition = myPosition->Next;
        return (*this);
    }

    List::const_iterator List::const_iterator::operator++ ( int )
    {
        const_iterator old(*this);
        ++(*this);
        return (old);
    }

    bool List::const_iterator::operator== ( const const_iterator& other ) const
    {
        return (myPosition == other.myPosition);
    }

    bool List::const_iterator::operator!= ( const const_iterator& other ) const
    {
        return (myPosition != other.myPosition);
    }

} }
