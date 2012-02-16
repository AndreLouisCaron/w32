#ifndef _w32_ts2_Folder_hpp__
#define _w32_ts2_Folder_hpp__

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

    class Folders;
    class Service;

        /*!
         * @brief Way to organise tasks in a hierarchical fashion.
         */
    class Folder :
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
