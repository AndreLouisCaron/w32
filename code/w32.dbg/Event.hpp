#ifndef _w32_dbg_Event_hpp__
#define _w32_dbg_Event_hpp__

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

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/types.hpp>

namespace w32 { namespace dbg {

    /*!
     * @brief Persistant, standard, localizable, logging mechanism.
     */
    class Event
    {
        /* nested types. */
    public:
        class Type;
        typedef word Category;
        typedef dword Message;

        /* construction. */
    public:
        virtual ~Event () {
        }

        /* methods. */
    public:
        /*!
         * @brief System-defined event category identifier.
         */
        virtual Type type () const = 0;

        /*!
         * @brief Application-defined numerical message identifier.
         */
        virtual Message message () const = 0;

        /*!
         * @brief Application-defined event category identifier.
         */
        virtual Category category () const {
            return (Category(0));
        }

        /*!
         * @brief Message argument count.
         */
        virtual word argc () const {
            return (0);
        }

        /*!
         * @brief Message argument values.
         */
        virtual const wchar_t ** argv () const {
            return (0);
        }
    };

    /*!
     * @brief Enumeration of system-defined event category identifiers.
     */
    class Event::Type
    {
        /* class data. */
    public:
        /*! @brief Indicates a noteworthy event. */
        static const Type success ();

        /*! @brief Indicates failure to accomplish some action. */
        static const Type error ();
        /*! @brief Indicates failure to accomplish some optional action. */
        static const Type warning ();

        /*! @brief Regular notification, should be used by default. */
        static const Type information ();

        static const Type auditsuccess ();
        static const Type auditfailure ();
        static const Type all ();

        /* nested types. */
    public:
        typedef word Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        // For internal use only.
        Type ( Value value );

        /* methods. */
    public:
        /*!
         * @brief The native code representing the type.
         */
        Value value () const;

        /* operators. */
    public:
        /*!
         * @brief The native code representing the type.
         */
        operator Value () const;
    };


} }

#endif /* _w32_dbg_Event_hpp__ */
