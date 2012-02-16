#ifndef _w32_ts_Action_hpp__
#define _w32_ts_Action_hpp__

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

namespace w32 { namespace ts {

        /*!
         * @brief Action performed when the trigger for a task is signled.
         */
    class Action :
        public com::Wrapper< ::IAction >
    {
        /* nested types. */
    public:
        class Type;

        /* construction. */
    public:
            /*!
             * @brief Wraps an existing action object.
             */
        explicit Action ( ::IAction * object );

        /* methods. */
    public:
            /*!
             * @brief Obtains the type code of the undelying object.
             */
        Type type () const;

            /*!
             * @brief Sets the identifier for the action.
             */
        void identifier ( const bstring& value );

            /*!
             * @brief Obtains the identifier for the action.
             */
        bstring identifier () const;
    };

        /*!
         * @brief Type-code for different types of actions.
         */
    class Action::Type
    {
        /* nested types. */
    public:
        typedef ::TASK_ACTION_TYPE Value;

        /* class data. */
    public:
        static const Type command ();
        static const Type handler ();
        static const Type email ();
        static const Type message ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
            // For internal use only.
        Type ( Value value )
            : myValue(value)
        {}

        /* class methods. */
    public:
            /*!
             * @brief Obtains the type-code for an existing action.
             */
        static Type of ( const Action& action );

        /* methods. */
    public:
            /*!
             * @brief Obtains the native value of the type-code.
             */
        Value value () const {
            return (myValue);
        }
    };

} }

#endif /* _w32_ts_Action_hpp__ */
