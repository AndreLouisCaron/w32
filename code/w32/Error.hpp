#ifndef _w32_Error_hpp__
#define _w32_Error_hpp__

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
#include <w32/types.hpp>
#include <w32/Language.hpp>
#include <iostream>
#include <locale>

namespace w32 {

    class string;

        /*
         "basic_error<ERROR_FILE_NOT_FOUND>" is used by a macro that
         allows the wrapping function to simply list all handled
         error codes.

         "FileNotFound" is used by client code to explicitly name
         errors, leading to clean and natural code. Also, this lets
         the wrapping class to use names reflecting the high-level
         meaning of the error code!

         "Error(ERROR_FILE_NOT_FOUND)" is used by the type system to
         fallback unto a generic handler. Most of the Win32c API indicate
         to call "GetLastError()" when something goes wrong, but don't
         provide a list of possible error codes. Thefore, this mechanism
         is used as a generic fallback to help improve the library: errors
         are always signaled, and as we learn the possible error codes
         raised by functions, we add meaningful types!
         */

    /*!
     * @ingroup w32
     * @brief Occurs when a Win32c library call fails.
     *
     * This is merely a debugging aid used because Microsoft's documentation
     * for the Win32c API does not specify which error codes may be
     * returned by it's functions. This is a backup for errors that were not
     * specifically checked for in order to prevent silent failures.
     *
     * When a function does not document it's errors, simply throw this. As
     * specific error codes are discovered for that function, add a check
     * for that error code and signal a specific error.
     */
    class Error
    {
        /* nested types. */
    public:
        typedef dword Code;

        class Put;

        /* data. */
    private:
        Code myCode;

        /* construction. */
    public:
        Error ( Code code ) throw();

        /* methods. */
    public:
        Code code () const throw();
        string what () const;
    };

        // Allows inserting a preferred language into a stream.
    class Error::Put :
        public std::locale::facet
    {
        /* class data. */
    public:
            // Might be uninitialized, because of DLL startup...
        static std::locale::id id;

        // No maximum length for error messages is documented. However, they
        // are normally very concise, so this should be enough. Resort to
        // this to avoid dynamic memory allocation while in stack unwinding.
        // That would cause the process to be aborted and we would never
        // know what went wrong: this is especially important since most
        // uses of this class are expected to be obscure and hard to
        // reproduce.
        static const size_t MaxMessageLength = 128;

        /* data. */
    private:
        const Language myLanguage;

        /* construction. */
    public:
        Put ( const Language& language, std::size_t refs = 0 )
            : std::locale::facet(refs), myLanguage(language)
        {
        }

        /* methods. */
    public:
        Language language () const
        {
            return (myLanguage);
        }
    };

        // Imbue new facet with locale for selected language!
    template< typename Char, typename Traits > inline
    std::basic_ostream<Char,Traits>& operator<<
        ( std::basic_ostream<Char,Traits>& out, const Language& language )
    {
        const Error::Put *const facet = new Error::Put(language);
        std::basic_ostream<Char,Traits>::sentry _(out);
        if ( _ ) {
            out.imbue(std::locale(out.getloc(), facet));
        }
        return (out);
    }

        // Output error message!
    inline std::ostream& operator<< ( std::ostream& out, const Error& error )
    {
        const Error::Put default_language(Language::neutral());
        std::ostream::sentry _(out);
        if ( _ )
        {
                // Query facet specifying language.
            const std::locale locale = out.getloc();
            const Error::Put& facet = std::has_facet<Error::Put>(locale)?
                std::use_facet<Error::Put>(locale) : default_language;
            
                // Format error message in that language.
            const ::LANGID language = facet.language();
            const ::DWORD flags = FORMAT_MESSAGE_FROM_SYSTEM;
            ::CHAR buffer[Error::Put::MaxMessageLength] = { 0 };
            const ::DWORD result = ::FormatMessageA(
                flags, 0, error.code(), language, buffer, sizeof(buffer)-1, 0
                );
            if ( result == 0 ) {
                out.setstate(std::ios_base::failbit); return (out);
            }
                // Remove trailing '\n'.
            if ( result < 2 ) {
                buffer[0] = '\0';
            }
            else {
                buffer[result-2] = '\0';
            }
            
                // Output to the stream!
            if ( out << buffer ) {
                out.setstate(std::ios_base::goodbit);
            }
        }
        return (out);
    }

    inline std::wostream& operator<< ( std::wostream& out, const Error& error )
    {
        const Error::Put default_language(Language::neutral());
        std::wostream::sentry _(out);
        if ( _ )
        {
                // Query facet specifying language.
            const std::locale locale = out.getloc();
            const Error::Put& facet = std::has_facet<Error::Put>(locale)?
                std::use_facet<Error::Put>(locale) : default_language;
            
                // Format error message in that language.
            const ::LANGID language = facet.language();
            const ::DWORD flags = FORMAT_MESSAGE_FROM_SYSTEM;
            ::WCHAR buffer[Error::Put::MaxMessageLength] = { 0 };
            const ::DWORD result = ::FormatMessageW(
                flags, 0, error.code(), language, buffer, sizeof(buffer)-1, 0
                );
            if ( result == 0 ) {
                out.setstate(std::ios_base::failbit); return (out);
            }
                // Remove trailing '\n'.
            if ( result < 2 ) {
                buffer[0] = L'\0';
            }
            else {
                buffer[result-2] = L'\0';
            }
            
                // Output to the stream!
            if ( out << buffer ) {
                out.setstate(std::ios_base::goodbit);
            }
        }
        return (out);
    }

        // Fast way to map error codes to named types.
    template< ::DWORD Code >
    struct basic_error :
        public Error
    {
        basic_error () : Error(Code) {}
    };

        // Sample error-code-to-type mappings.
    typedef basic_error< ERROR_INVALID_HANDLE > InvalidHandle;
    typedef basic_error< ERROR_FILE_NOT_FOUND > FileNotFound;
    typedef basic_error< ERROR_MUI_FILE_NOT_FOUND > LanguageNotAvailable;

    // Shortcut to avoid writing if ( error == ERROR_... )
    // { throw (basic_error< ERROR_...>()); }
#define HANDLE_W32_ERROR(X)if ( error == X ) throw (basic_error< X >());

}

    // Use this macro to signal errors.
#define UNCHECKED_WIN32C_ERROR(function,error) \
    { ::DebugBreak(); throw (w32::Error(error)); }

#endif /* _w32_Error_hpp__ */
