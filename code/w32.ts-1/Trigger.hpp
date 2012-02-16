#ifndef _w32_ts_Trigger_hpp__
#define _w32_ts_Trigger_hpp__

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
#include <iosfwd>

namespace w32 { namespace ts {

    class Task;

    class Trigger :
        public w32::com::Wrapper< ::ITaskTrigger >
    {
        /* nested types. */
    public:
        class Type
        {
        friend class Trigger;

        /* nested types. */
        public:
            typedef ::TASK_TRIGGER_TYPE Value;

            /* class data. */
        public:
            static const Type once ();
            static const Type daily ();
            static const Type weekly ();
            static const Type idle ();
            static const Type start ();
            static const Type logon ();

            /* data. */
        private:
            Value myValue;

            /* construction. */
        private:
                // For internal use only!
            Type ( Value value )
                : myValue(value)
            {}

            /* methods. */
        public:
            Value value () const {
                return (myValue);
            }

            /* operators. */
        public:
            bool operator== ( const Type& other ) const {
                return (myValue == other.myValue);
            }

            bool operator!= ( const Type& other ) const {
                return (myValue != other.myValue);
            }

            friend std::ostream& operator<<
                ( std::ostream& out, const Type& type );
            friend std::wostream& operator<<
                ( std::wostream& out, const Type& type );
        };

            /*!
             * @brief Write access to trigger and auto-commit.
             */
        class Editor :
             private NotCopyable
        {
            /* nested types. */
        public:
            typedef ::TASK_TRIGGER Data;

            /* data. */
        private:
            Trigger& myTrigger;
            Data& myData;

            /* construction. */
        public:
                /*!
                 * @brief Open for write-access.
                 */
            Editor ( Trigger& trigger );

            /* methods. */
        public:
            void start ( int year, int month, int day );

                /*!
                 * @brief Setup trigger for daily execution.
                 */
            void daily ( ::WORD interval, int hour, int month );

                /*!
                 * @brief Commits changes (assign to trigger object).
                 */
            void commit () const;
        };
        friend class Editor;

    private:
            /*!
             * @brief Wraps trigger data.
             */
        class Data
        {
            /* data. */
        private:
            ::TASK_TRIGGER myValue;

            /* construction. */
        public:
            Data ( ::ITaskTrigger& trigger );
            Data ();

            /* methods. */
        public:
            ::TASK_TRIGGER& get ();
            const ::TASK_TRIGGER& get () const;
        };

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
            /*!
             * @brief Add a new trigger to an exising task.
             */
        Trigger ( const Task& task );

            /*!
             * @brief Open an existing trigger for an exising task.
             */
        Trigger ( const Task& task, const ::WORD& index );

        /* methods. */
    public:
            /*!
             * @brief Get the type of trigger.
             */
        const Type type () const;
    };

} }

#endif /* _w32_ts_Trigger_hpp__ */
