#ifndef _w32_ConsoleEventHandler_hpp__
#define _w32_ConsoleEventHandler_hpp__

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
 * @file w32/ConsoleEventHandler.hpp
 */

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>

namespace w32 {

    //! @addtogroup w32
    //! @{

    /*!
     * @brief Console event handler resgistration.
     *
     * Installing a console event handler allows your console application to
     * intercept control-C, control-break, console close events and the like.
     * This allows you to perform proper shutdown even if your main loop is
     * blocking on some specific event (provided that you can unblock it at
     * will).
     *
     * Console event handlers are registered in a LIFO (stack) order.  The last
     * console event handler is called first.  If the first (most recently
     * installed) event handler does not process the event, the second handler
     * is called and so forth.
     */
    class ConsoleEventHandler :
        private NotCopyable
    {
        /* nested types. */
    public:
        typedef ::PHANDLER_ROUTINE Function;

        /* data. */
    private:
        Function myFunction;

        /* construction. */
    public:
        /*!
         * @brief Installs @a function as a console event handler.
         */
        ConsoleEventHandler (Function function);

        /*!
         * @brief Removes the console event handler installed.
         */
        ~ConsoleEventHandler ();
    };

    //! @}

}

#endif /* _w32_ConsoleEventHandler_hpp__ */
