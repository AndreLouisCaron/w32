// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/EventQueue.hpp>

namespace w32 { namespace gdi {

    const EventQueue::Filter EventQueue::Filter::any ()
    {
        return (Filter(0,0));
    }

    const EventQueue::Filter EventQueue::Filter::input ()
    {
        return (Filter(WM_INPUT, WM_INPUT));
    }

    EventQueue::Filter::Filter ( uint first, uint last )
        : myFirst(first), myLast(last)
    {
    }

    uint EventQueue::Filter::first () const
    {
        return (myFirst);
    }

    uint EventQueue::Filter::last () const
    {
        return (myLast);
    }

} }
