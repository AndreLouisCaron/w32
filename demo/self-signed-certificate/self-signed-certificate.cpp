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

/*!
 * @file demo/self-signed-certificate/self-signed-certificate.cpp
 */

#include <w32.hpp>
#include <w32.cr.hpp>

#include <w32/app/console-program.hpp>

namespace {

    /*!
     * @brief Get a cryptographic provider that operates on @a container.
     * @param container The name of the container to open.
     * @return A cryptographic provider.
     *
     * If the container does not already exists, the function creates it.
     */
    w32::cr::Provider get_provider ( const w32::string& container )
    {
        const w32::cr::Provider::Type type  =
            w32::cr::Provider::Type::rsafull();

        // Try creating the key in an existing container.
        w32::cr::Provider::Hints hints;
        hints
            .machineKeySet()
            ;
        try {
            return (w32::cr::Provider(type, hints, container));
        }
        catch (const w32::Error& error)
        {
            // If the container does not exist, create it.
            if (error.code() != NTE_BAD_KEYSET) {
                throw;
            }
            hints
                .newKeySet()
                ;
            return (w32::cr::Provider(type, hints, container));
        }
    }

    int run ( int argc, wchar_t ** argv )
    {
        // Access the provider and create or update the container.
        w32::cr::Provider provider = get_provider(L"my-new-container");

        // Generate a certificate.
        const w32::string subject =
            L"CN=Example,"
            L"O=Example Inc.,"
            L"E=admin@example.qc.ca,"
            L"C=Canada,"
            L"S=QC,"
            ;
        const w32::cr::Certificate certificate =
            w32::cr::Certificate::self_signed(provider, subject);
        if (certificate.valid())
        {
            std::cout
                << "Successfully generated a certificate."
                << std::endl;
        }
        else {
            std::cerr
                << "Generated an invalid certificate!"
                << std::endl;
        }

        return (EXIT_SUCCESS);
    }

}

#include <w32/app/console-program.cpp>
