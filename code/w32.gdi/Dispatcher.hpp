#ifndef _w32_gdi_Dispatcher_hpp__
#define _w32_gdi_Dispatcher_hpp__

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
#include <w32.gdi/callback.hpp>
#include <w32.gdi/Notification.hpp>
#include <w32.gdi/Window.hpp>
#include <algorithm>
#include <vector>

namespace w32 { namespace gdi {

        // Useful dispatch table.
    template<class Mediator>
    class Dispatcher
    {
        /* nested types. */
    public:
        typedef void(*notification_callback)(Mediator&,const ::NMHDR*);

        class Handler
        {
            ::HWND mySource;
            ::UINT myNotification;
            notification_callback myCallback;
        public:
            Handler ( ::HWND source, uint notification, notification_callback callback )
                : mySource(source),
                  myNotification(notification),
                  myCallback(callback)
            {}
            ::HWND source () const { return (mySource); }
            ::UINT notification () const { return (myNotification); }
            void invoke ( Mediator& mediator ) const
            {
                myCallback(mediator, 0);
            }

            void invoke ( Mediator& mediator, const ::NMHDR * header ) const
            {
                myCallback(mediator, header);
            }
        };

        class Matches
        {
            ::HWND mySource;
            ::UINT myNotification;
        public:
            Matches ( Window& source, ::UINT message )
                : mySource(source.handle()),
                  myNotification(message)
            {}
            bool operator() ( const Handler& handler ) const
            {
                return ((handler.source() == mySource)
                    && (handler.notification() == myNotification));
            }
        };

        /* data. */
    private:
        std::vector< Handler > myHandlers;
        Mediator& myMediator;

        /* construction. */
    public:
        Dispatcher ( Mediator& mediator )
            : myMediator(mediator)
        {
        }

        /* methods. */
    public:
            // register a WM_COMMAND handler.
        template<class Control, uint Code>
        Dispatcher< Mediator >& add
            ( Control& source, Notification<Control,Code,void>, delegate<Mediator,void> call )
        {
            myHandlers.push_back(Handler(source.handle(), Code, call));
            return (*this);
        }

            // register a WM_NOTIFY handler.
        template<class Control, uint Code, typename Argument>
        Dispatcher< Mediator >& add
            ( Control& source, Notification<Control,Code,Argument>,
              delegate<Mediator,Argument> call )
        {
            myHandlers.push_back(Handler(source.handle(), Code, call));
            return (*this);
        }

            // register a WM_NOTIFY handler.
        template<class Control, uint Code, typename Argument>
        Dispatcher< Mediator >& add
            ( Control& source, Notification<Control,Code,Argument>,
              delegate<Mediator,void> call )
        {
            myHandlers.push_back(Handler(source.handle(), Code, call));
            return (*this);
        }

        /* operators. */
    public:
        bool operator() ( Window& source, ::UINT message )
        {
                // Search table for (source.handle(), message.wm()) match.
            const Matches predicate(source, message);
            const std::vector< Handler >::const_iterator match =
                std::find_if(myHandlers.begin(), myHandlers.end(), predicate);
            
                // If callback is found, invoke it!
            if ( match != myHandlers.end() ) {
                match->invoke(myMediator);
                return (true);
            }
            
            return (false);
        }

        bool operator() ( Window& source, const ::NMHDR * header )
        {
                // Search table for (source.handle(), message.wm()) match.
            const Matches predicate(source, header->code);
            const std::vector< Handler >::const_iterator match =
                std::find_if(myHandlers.begin(), myHandlers.end(), predicate);
            
                // If callback is found, invoke it!
            if ( match != myHandlers.end() ) {
                match->invoke(myMediator, header);
                return (true);
            }
            
            return (false);
        }
    };


} }

#endif /* _w32_gdi_Dispatcher_hpp__ */
