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
