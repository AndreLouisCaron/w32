#ifndef _w32_ipc_Startup__
#define _w32_ipc_Startup__

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
#include <w32/Environment.hpp>
#include <w32/string.hpp>
#include <w32/types.hpp>
#include <w32/Object.hpp>
#include <map>

namespace w32 { namespace io {

    class InputStream;
    class OutputStream;

} }

namespace w32 { namespace ipc {

    class Process;

    /*!
     * @brief Helps build a process startup context.
     */
    class Startup
    {
        /* data. */
    private:
        string myProgram;
        string myCommand;
        string myLocation;
        dword myFlags;
        bool myInherit;
        std::map<string,string> myEnvironment;

        dword myState;

        string myDesktop;
        string myTitle;
        dword myX;
        dword myY;
        dword myWidth;
        dword myHeight;
        word myShowCommand;
        Object::Handle myStdi;
        Object::Handle myStdo;
        Object::Handle myStde;

        /* construction. */
    public:
        Startup ();

        /* methods. */
    public:
        Startup& program ( const string& path );
        Startup& location ( const string& path );
        Startup& command ( const string& command );
        Startup& clear_environment ();

        /*!
         * @brief Insert all of the current process' environment variables.
         * @return The startup instance, for method chaining.
         *
         * Duplicates do not overwrite existing values.
         */
        Startup& inherit_environment ();

        /*!
         * @brief Insert all environment variables in a specific environment.
         * @param environment The environment to merge.
         * @return The startup instance, for method chaining.
         *
         * Duplicates do not overwrite existing values.
         */
        Startup& inherit_environment( const Environment::Map& environment );

        /*!
         * @brief Insert a variables in the environment.
         * @param field The variable's name.
         * @param value The variable's value.
         *
         * Duplicates do not overwrite existing values.
         */
        Startup& add_to_environment( const string& field, const string& value );

        Startup& breakawayFromJob ();
        Startup& defaultErrorMode ();
        Startup& newConsole ();
        Startup& newProcessGroup ();
        Startup& noWindow ();
        Startup& protectedProcess ();
        Startup& preserveCodeAuthorizationLevel ();
        Startup& suspended ();
        Startup& debugOnlyThisProcess ();
        Startup& debugThisProcessTree ();
        Startup& detachedProcess ();

        Startup& inheritHandles ();
        Startup& stdi ( io::InputStream stream );
        Startup& stdo ( io::OutputStream stream );
        Startup& stde ( io::OutputStream stream );

        Startup& desktop ( const string& name );
        Startup& title ( const string& text );
        Startup& showWindow ( word command );
        Startup& position ( dword x, dword y );
        Startup& size ( dword width, dword height );

        /*!
         * @brief Create a process with the current context state.
         */
        Process spawn () const;
    };

} }

#endif /* _w32_ipc_Startup__ */
