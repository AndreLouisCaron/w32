#ifndef _w32_ts_Action_hpp__
#define _w32_ts_Action_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace ts {

        /*!
         * @brief Action performed when the trigger for a task is signled.
         */
    class W32_TS2_EXPORT Action :
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
    class W32_TS2_EXPORT Action::Type
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
