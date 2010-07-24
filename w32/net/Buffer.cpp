// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/net/Buffer.hpp>
#include <algorithm>

namespace w32 { namespace net {

    Buffer::Buffer ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
    }

    Buffer::Buffer ( iterator begin, size_type size )
    {
        myData.buf = begin;
        myData.len = size;
    }

    Buffer::Buffer ( iterator begin, iterator end )
    {
        myData.buf = begin;
        myData.len = std::distance(begin, end);
    }

    Buffer::Data& Buffer::data ()
    {
        return (myData);
    }

    const Buffer::Data& Buffer::data () const
    {
        return (myData);
    }

    Buffer::iterator Buffer::begin ()
    {
        return (myData.buf);
    }

    Buffer::const_iterator Buffer::begin () const
    {
        return (myData.buf);
    }

    Buffer::iterator Buffer::end ()
    {
        return (myData.buf + myData.len);
    }

    Buffer::const_iterator Buffer::end () const
    {
        return (myData.buf + myData.len);
    }

} }
