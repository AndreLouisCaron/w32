#ifndef _w32_gdi_Dispatcher_hpp__
#define _w32_gdi_Dispatcher_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/gdi/callback.hpp>
#include <w32/gdi/Notification.hpp>
#include <w32/gdi/Window.hpp>
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
