#ifndef _w32_Module_hpp__
#define _w32_Module_hpp__

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
#include <w32/astring.hpp>
#include <w32/Reference.hpp>
#include <w32/string.hpp>

namespace w32 {

    /*!
     * @ingroup w32
     * @brief Loaded executable image: program or library.
     *
     * Native executable image; this covers both executables (EXE) and
     * dynamically-linked librairies (DLL). This class allows refering to
     * loaded modules, including the current module, as well as loading
     * external modules at run-time.
     */
    class Module
    {
        /* nested types. */
    public:
        /*!
         * @brief Native identifier for a module.
         */
        typedef Reference< ::HMODULE, void(*)(::HMODULE) > Handle;

        /* class methods. */
    public:
        /*!
         * @param object Existing module handle.
         * @return A handle that will release @a object.
         */
        static Handle claim ( ::HMODULE object );

        /*!
         * @param object Existing module handle.
         * @return A handle that will @e not release @a object.
         */
        static Handle proxy ( ::HMODULE object );

        /*!
         * @param path Executable or dynamic library file path.
         * @return A fully loaded module.
         *
         * @note Loading is subject to library search paths when using only a
         *  file name.  If you know exactly where the module can be found,
         *  providing the absolute path is safer.
         */
        static Module load ( const string& path );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        /*!
         * @brief Wrap an existing module handle.
         */
        explicit Module ( const Handle& handle );

        /*!
         * @brief Get the executable module for the current process.
         */
        Module ();

        /*!
         * @brief Locates an already loaded module by name.
         * @param name Name of the module to find.
         */
        explicit Module ( const string& name );

        /* methods. */
    public:
        /*!
         * @return The module's handle.
         */
        const Handle& handle () const;

        /*!
         * @return The module's file name.
         */
        string name () const;

        /*!
         * @return The module's absolute file path.
         */
        string path () const;

        /*!
         * @brief Obtains a raw pointer to a DLL-exported symbol by name.
         * @param symbol The requested symbol's name.
         * @return A pointer to the requested symbol if found, else 0.
         *
         * The symbol's type is not part of the export information, so it is up
         * to the caller to cast the pointer to the appropriate type.
         */
        void * get ( const astring& symbol ) const;

        /*!
         * @brief Obtains a typed pointer to a DLL-exported symbol by name.
         * @param symbol The requested symbol's name.
         * @return A pointer to the requested symbol if found, else 0.
         *
         * The symbol's type is not part of the export information, so it is up
         * to the caller to cast the pointer to the appropriate type.
         */
        template<typename Pointer>
        Pointer get ( const astring& symbol ) const
        {
            Pointer value = 0;
            *reinterpret_cast<void**>(&value) = get(symbol);
            return (value);
        }
    };

}

#endif /* _w32_Module_hpp__ */
