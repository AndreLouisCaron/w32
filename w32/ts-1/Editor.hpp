#ifndef _w32_ts_Editor_hpp__
#define _w32_ts_Editor_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>

namespace w32 { namespace ts {

    class Task;

        /*!
         * @brief Write-access to a task object.
         */
    class W32_TS_EXPORT Editor :
        private NotCopyable
    {
        /* data. */
    private:
        Task& myTask;

        /* construction. */
    public:
        Editor ( Task& task );

        /* methods. */
    public:
        void application ( const string& value );
        void arguments ( const string& value );
        void creator ( const string& value );
        void account ( const string& value );
        void account ( const string& value, const string& password );

            /*!
             * @brief Commit changes (save to persistent file).
             */
        void commit ();
    };

} }

template<> inline w32::com::Guid
    w32::com::guidof< ::IPersistFile > ()
{
    return (IID_IPersistFile);
}

#endif /* _w32_ts_Editor_hpp__ */
