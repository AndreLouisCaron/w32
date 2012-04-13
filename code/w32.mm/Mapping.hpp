#ifndef _w32_mm_Mapping_hpp__
#define _w32_mm_Mapping_hpp__

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
#include <w32/Object.hpp>
#include <w32/types.hpp>
#include <w32.fs/File.hpp>

namespace w32 { namespace mm {

    /*!
     * @ingroup w32-mm
     *
     * @brief Direct file-to-memory mapping.
     *
     * Segment of virtual memory to which is assigned a byte-for-byte
     * correlation with some portion of a file.
     *
     * Memory-mapped files lead to increased I/O performance, especially for
     * smaller files.  For starters, reading from memory is faster than using a
     * system call to read a portion of a file.  Moreover, the mapped region is
     * the kernel's page cache, avoiding a copy of the data in user space.
     */
    class Mapping :
        public Object
    {
        /* nested types. */
    public:
        /*!
         * @brief Enumeration of file mapping modes.
         */
        class Mode
        {
            /* nested types. */
        public:
            /*!
             * @brief Native mapping mode representation.
             */
            typedef ::DWORD Value;

            /* values. */
        public:
            /*! @brief Maps a file into memory as read-only. */
            static Mode i ();

            /*! @brief Maps a file into memory as write-only. */
            static Mode o ();

            /* data. */
        private:
            Value myValue;

            /* construction. */
        private:
            // For inteernal use only.
            Mode ( Value value );

            /* methods. */
        public:
            /*!
             * @return The native representation of the mapping mode.
             */
            Value value () const;

            /* operators. */
        public:
            /*!
             * @return The native representation of the mapping mode.
             */
            operator Value () const;
        };

        class View;

        /* data. */
    private:
        Mode myMode;

        /* construction. */
    public:
        /*!
         * @brief Reserves one or more pages of memory for a file mapping.
         *
         * If @a size is 0, the entire file will be mapped.
         */
        Mapping ( fs::File& file, Mode mode, qword size = 0 );

        /* methods. */
    public:
        Mode mode () const;
    };

    /*!
     * @brief Selection of what portion to map into memory.
     */
    class Mapping::View
    {
        /* nested types. */
    private:
        typedef Reference< void* > Handle;

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        /*!
         * @brief Maps a portion of the file to a page of memory.
         * @param mapping File mapping object backing the view.
         * @param offset Offset, in bytes, from the start of the file.
         * @param amount Number of bytes to map. If this is 0, all bytes
         *  starting from @a offset, are mapped into memory.
         *
         * The file mapping actually only reserves an area in memory.  A view
         * of the file maps the contents of the file onto that reserved page.
         */
        View ( Mapping& mapping, qword offset=0, dword amount=0 );

        /* methods. */
    public:
        /*!
         * @brief Obtains the base address for the view.
         */
        void * location ();

        /*!
         * @brief Write to disk to reflect the contents of memory.
         * @param amount Number of bytes, starting from the base of the view,
         *  to commit to disk.
         *
         * No matter the amount to flush, the commit range always starts at the
         * base of the view.  If @a amount is 0 (the default), all of the view
         * is commited.
         */
        void flush ( dword amount = 0 );
    };

} }

#endif /* _w32_mm_Mapping_hpp__ */
