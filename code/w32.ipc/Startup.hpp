#ifndef _w32_ipc_Startup__
#define _w32_ipc_Startup__

// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
