#ifndef _w32_ts_Trigger_hpp__
#define _w32_ts_Trigger_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <iosfwd>

namespace w32 { namespace ts {

    class Task;

    class W32_TS_EXPORT Trigger :
        public w32::com::Wrapper< ::ITaskTrigger >
    {
        /* nested types. */
    public:
        class W32_TS_EXPORT Type
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

            friend W32_TS_EXPORT std::ostream& operator<<
                ( std::ostream& out, const Type& type );
            friend W32_TS_EXPORT std::wostream& operator<<
                ( std::wostream& out, const Type& type );
        };

            /*!
             * @brief Write access to trigger and auto-commit.
             */
        class W32_TS_EXPORT Editor :
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
