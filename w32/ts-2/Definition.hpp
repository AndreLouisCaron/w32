#ifndef _w32_ts2_Definition_hpp__
#define _w32_ts2_Definition_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace ts {

    class Registration;
    class Service;

    class W32_TS2_EXPORT Definition :
        public com::Wrapper< ::ITaskDefinition >
    {
        /* construction. */
    public:
            /*!
             * @brief Creates a new task definition for a given scheduler.
             *
             * To actually register the task, invoke the appropriate
             * \c RegisteredTask constructor.
             */
        explicit Definition ( Service& service );

            /*!
             * @brief Obtains the definition of a registered task.
             */
        explicit Definition ( const Registration& task );
    };

} }

#endif /* _w32_ts2_Definition_hpp__ */
