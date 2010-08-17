#ifndef _w32_ts2_Folder_hpp__
#define _w32_ts2_Folder_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace ts {

    class Folders;
    class Service;

        /*!
         * @brief Way to organise tasks in a hierarchical fashion.
         */
    class W32_TS2_EXPORT Folder :
        public com::Wrapper< ::ITaskFolder >
    {
        /* class methods. */
    public:
        static Folder create ( Folder& parent, const bstring& name );

        /* construction. */
    private:
            // For internal use only.
        explicit Folder ( ::ITaskFolder * instance );

    public:
            /*!
             * @brief Opens the root folder for the task service.
             */
        explicit Folder ( Service& service );

            /*!
             * @brief Opens a specific folder in the task service.
             */
        Folder ( Service& service, const bstring& path );

            /*!
             * @brief Opens a specific sub-folder in a task service folder.
             */
        Folder ( Folder& parent, const bstring& path );

            /*!
             * @brief Opens a specific sub-folder in a folder collection.
             *
             * @param index 1-based index to the desired folder.
             */
        Folder ( const Folders& list, long index );

            /*!
             * @brief Opens a specific sub-folder in a folder collection.
             */
        Folder ( const Folders& list, const bstring& name );

        /* methods. */
    public:
            /*!
             * @brief Obtains the name of the folder.
             */
        bstring name () const;

            /*!
             * @brief Obtains the path to the folder.
             */
        bstring path () const;
    };

} }

#endif /* _w32_ts2_Folder_hpp__ */
