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
