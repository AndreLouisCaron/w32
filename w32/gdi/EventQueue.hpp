#ifndef _w32_gdi_EventQueue_hpp__
#define _w32_gdi_EventQueue_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "../__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/gdi/Event.hpp>
#include <w32/gdi/Message.hpp>

namespace w32 { namespace gdi {

    class W32_GDI_EXPORT EventQueue :
        private NotCopyable
    {
        /* nested types. */
    public:
        class W32_GDI_EXPORT Filter
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
