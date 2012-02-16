#ifndef _w32_gdi_Dialog_hpp__
#define _w32_gdi_Dialog_hpp__

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
#include <w32/Module.hpp>
#include <w32/string.hpp>
#include <w32/types.hpp>
#include <w32/Resource.hpp>
#include <w32.gdi/Window.hpp>

namespace w32 { namespace gdi {

        /*!
         * @brief Shorthand to writing simple windows.
         */
    class Dialog :
        public virtual Window
    {
        /* nested types. */
    public:
            /*!
             * @brief Allows creation of in-memory dialog templates.
             *
             * Dialog templates allow you to define the list of controls you
             * wish to host before you even create the window. Moreover, the
             * system uses an internal window class: this avoids you the trouble
             * of registering one yourself.
             */
        class Template;

            /*!
             * @brief Integer type used to return information from the Callback
             *   function and the dialog invocation.
             */
        typedef intptr Result;

            /*!
             * @brief System hook for sending us control notifications.
             *
             * This is usually a complex and @e overly redundant function.
             *
             * @param hdlg Handle to the dialog window.
             * @param msg Window message.
             * @param wp Extra message information.
             * @param lp Extra message information.
             * @return Message dependant status code.
             */
        typedef Result ( __stdcall * Callback )
            ( ::HWND hdlg, uint msg, wparam wp, lparam lp );

            /*!
             * @brief One possible implementation of a Callback function.
             *
             * This function implements a basic dispatcher by mapping a Handler
             * callback set to an executable Callback function with the proper
             * signature.
             *
             * To easily create a callback for you dialog, simply subclass the
             * default callback set and "override" the appropriate method(s).
             */
        template<typename H> static Result __stdcall adapt
            ( ::HWND, uint, wparam, lparam );

            /*!
             * @brief Default callback set.
             */
        struct Handler;

        /* class methods. */
    public:
            // Shows a modeless dialog box from a resource template.
        static Result show ( const Resource& template_ );
        static Result show ( const Resource& template_, Callback callback );

            // Shows a modal dialog box from an resource template.
        static Result show ( const Window& parent, const Resource& template_ );
        static Result show (
            const Window& parent, const Resource& template_, Callback callback );

            // Shows a modeless dialog box from an in-memory template.
        static Result show ( const Template& template_ );
        static Result show ( const Template& template_, Callback callback );

            // Shows a modal dialog box from an in-memory template.
        static Result show ( const Window& parent, const Template& template_ );
        static Result show (
            const Window& parent, const Template& template_, Callback callback );

        /* construction. */
    public:
        explicit Dialog ( const Handle& handle );
        explicit Dialog (
            const Template& template_, const Module& module = Module()
            );

        /* methods. */
    public:
            // Don't hide inherited members!
        using Window::show;

            /*!
             * @brief Closes a modal dialog and returns control to the caller.
             *
             * @note This only closes model dialogs invoked with one of the
             *   Dialog::show() methods or their low-level @c DialogBox*()
             *   counterparts. Other dialogs, shown with the Window::show()
             *   family (and respective low-level @c ShowWindow() versions)
             *   must be hidden with the Window::hide() methods.
             *
             * @param status Dialog exit code, used to provide extra info. This
             *   value is often used as a binary switch (confirm/cancel).
             */
        void end ( intptr status = 0 );

            /*!
             * @brief Manual @c SendMessage() call for dialog item.
             * @return Message dependant value...
             */
        lresult send ( word identifier, uint msg, wparam wp, lparam lp );

            /*!
             * @brief Indicates if a check-box control is checked.
             */
        bool checked ( word identifier ) const;

            /*!
             * @brief Indicates if a check-box control is not checked.
             */
        bool unchecked ( word identifier ) const;

            /*!
             * @brief Obtains the caption associated to a control.
             * @return The control's caption.
             */
        string caption ( word identifier ) const;

            /*!
             * @brief Changes the caption associated to a control.
             */
        void caption ( word identifier, const string& text );
    };

        // Long and painful dispatcher...
    template<typename H> Dialog::Result __stdcall Dialog::adapt
        ( ::HWND hdlg, uint message, wparam wp, lparam lp )
    {
        const word item = LOWORD(wp);
        Dialog dialog(hdlg);
        
        if ( message == WM_INITDIALOG )
        {
            return (H::initialize(dialog));
        }
        else if ( message == WM_COMMAND )
        {
            //ControlProxy control(reinterpret_cast<::HWND>(lp));
            return (H::command(dialog, HIWORD(wp), item));
        }
        else if ( message == WM_CLOSE )
        {
            return (H::close(dialog));
        }
        
            // Always accept default behaviour.
        return (0);
    }

    class Dialog::Template
    {
        /* nested types. */
    public:
        typedef ::DLGTEMPLATE Data;
        typedef ::DLGITEMTEMPLATE Item;

        /* data. */
    private:
        byte *const myStart;
        byte * myPosition;

        /* construction. */
    public:
        Template (
            byte * buffer, const Rectangle& bounds,
            uint8 items, const string& title
            );

        ~Template ();

        /* methods. */
    public:
        Template& button (
            const Rectangle& area, const string& caption, uint8 identifier
            );

        Template& checkbox (
            const Rectangle& area, const string& caption, uint8 identifier
            );

        Template& edit (
            const Rectangle& area, const string& caption, uint8 identifier
            );

        Template& label (
            const Rectangle& area, const string& text, word identifier=-1
            );

        Template& listbox (
            const Rectangle& area, uint8 identifier
            );

        Template& scrollbar (
            const Rectangle& area, uint8 identifier
            );

        Template& combobox (
            const Rectangle& area, uint8 identifier
            );

        const Data& data () const  {
            return (*reinterpret_cast<const ::DLGTEMPLATE*>(myStart));
        }
    };

        // Another long and painful dispatcher.
    struct Dialog::Handler
    {
            /*!
             * @brief Hook invoked right before the dialog is shown.
             *
             * This is a perfect time to define controls or set dialog and
             * control properties.
             *
             * @param dlg The dialog being initialized.
             */
        static Result initialize ( Dialog& dlg )
        {
                // Don't use the system default keyboard focus.
            return (0);
        }

            /*!
             * @brief Hook invoked when a control wants to signal an event or
             *   change of state to the dialog.
             *
             * Most default controls handle their own behaviour in a fantastic
             * fashion (provided they are granted with the appropriate style).
             * However, some state is inherently related to the parent dialog.
             * That state is signaled through this @c command notification.
             *
             * @param dlg The parent dialog.
             * @param ntf Control-dependant notification code.
             * @param item Control identifier.
             */
        static Result command ( Dialog& dlg, uint ntf, word item )
        {
                // Return false unless you want to exit the dialog.
            return (0);
        }

            /*!
             * @brief Hook invoked right before the dialog is closed.
             *
             * This is an appropriate time to ask the user if any unsaved state
             * should be kept or even if the close operation should be aborted.
             *
             * @note @e Close should be read as @e cancel: this method is
             *   invoked when the user selects alternate means to close the
             *   dialog's window (i.e. provided by the window manager).
             *
             * @param dlg The dialog to be destroyed.
             */
        static Result close ( Dialog& dlg )
        {
                // User closed the dialog window: exit!
            dlg.end(1);
            return (0);
        }
    };

} }

#endif /* _w32_gdi_Dialog_hpp__ */
