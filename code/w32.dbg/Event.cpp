// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.dbg/Event.hpp>

namespace w32 { namespace dbg {

    const Event::Type Event::Type::success ()
    {
        return (EVENTLOG_SUCCESS);
    }

    const Event::Type Event::Type::error ()
    {
        return (EVENTLOG_ERROR_TYPE);
    }

    const Event::Type Event::Type::warning ()
    {
        return (EVENTLOG_WARNING_TYPE);
    }

    const Event::Type Event::Type::information ()
    {
        return (EVENTLOG_INFORMATION_TYPE);
    }

    const Event::Type Event::Type::auditsuccess ()
    {
        return (EVENTLOG_AUDIT_SUCCESS);
    }

    const Event::Type Event::Type::auditfailure ()
    {
        return (EVENTLOG_AUDIT_FAILURE);
    }

    const Event::Type Event::Type::all ()
    {
        return (EVENTLOG_SUCCESS|
            EVENTLOG_ERROR_TYPE|
            EVENTLOG_WARNING_TYPE|
            EVENTLOG_INFORMATION_TYPE|
            EVENTLOG_AUDIT_SUCCESS|
            EVENTLOG_AUDIT_FAILURE);
    }

    Event::Type::Type ( Value value )
        : myValue(value)
    {
    }

    Event::Type::Value Event::Type::value () const
    {
        return (myValue);
    }

    Event::Type::operator Event::Type::Value () const
    {
        return (myValue);
    }

} }
