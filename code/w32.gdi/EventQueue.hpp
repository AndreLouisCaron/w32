#ifndef _w32_gdi_EventQueue_hpp__
#define _w32_gdi_EventQueue_hpp__

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
#include <w32/NotCopyable.hpp>
#include <w32.gdi/Event.hpp>
#include <w32.gdi/Message.hpp>

namespace w32 { namespace gdi {

    class EventQueue :
        private NotCopyable
    {
        /* nested types. */
    public:
        class Filter
        {
            /* class methods. */
        public:
            static const Filter any ();
            static const Filter input ();

            /* data. */
        private:
            uint myFirst;
            uint myLast;

            /* construction. */
        public:
            Filter ( uint first, uint last );

            /* methods. */
        public:
            uint first () const;
            uint last () const;
        };

        /* construction. */
    public:
        virtual ~EventQueue () {
        }

        /* methods. */
    public:
            /*!
             * @brief Removes a message from the queue, waiting if necessary.
             */
        virtual bool next ( Event& event, Filter filter = Filter::any() ) = 0;

            /*!
             * @brief Checks if a message is available.
             */
        virtual bool peek ( Event& event, Filter filter = Filter::any() ) = 0;

            /*!
             * @brief Adds a message to the top of the event queue.
             *
             * @note This function does not wait for the event to be processed.
             *    Use the \c Window::send() method for that behaviour.
             */
        virtual void post ( const Message& message ) = 0;
    };

} }

#endif /* _w32_gdi_EventQueue_hpp__ */
