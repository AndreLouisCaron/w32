#ifndef _win32c_security_ProcessToken_hpp__
#define _win32c_security_ProcessToken_hpp__

/*!
 * @file ProcessToken.hpp
 * @author Andre Caron
 */

#include "Token.hpp"
#include <win32c/pmgt/Process.hpp>
#include <win32c/pmgt/CurrentProcess.hpp>
#include <Windows.h>

namespace win32c { namespace security {

        /*!
         * @brief Access token for a process.
         */
    class ProcessToken :
        public Token
    {
        /* nested types. */
    public:
        class Handle :
            public Token::Handle
        {
            /* data. */
        private:
            ::HANDLE myValue;

            /* construction. */
        public:
            explicit Handle ( ::HANDLE value );
            virtual ~Handle ();

            /* overrides. */
        public:
            virtual ::HANDLE value () const;
        };

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit ProcessToken (
            const pmgt::Process& process = pmgt::CurrentProcess()
            );

        /* overrides. */
    public:
        virtual const Handle& handle () const;
    };

} }

#endif /* _win32c_security_ProcessToken_hpp__ */
