#ifndef _w32_gdi_Class_hpp__
#define _w32_gdi_Class_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Module.hpp>
#include <w32/NotCopyable.hpp>
#include <w32/Resource.hpp>
#include <w32.gdi/Atom.hpp>
#include <w32.gdi/Brush.hpp>
#include <w32.gdi/Cursor.hpp>
#include <w32.gdi/Icon.hpp>

namespace w32 { namespace gdi {

        /*!
         * @brief Description for a familiy of windows.
         *
         * You should have only one instance of this class per registration.
         */
    class Class
    {
        /* nested types. */
    public:
        typedef ::WNDCLASSEXW Data;

        class Style;

        /* data. */
    private:
            // The structure must hold a pointer to the string. Make sure to own
            // the memory referenced by the structure as long as it can be used.
        string myName;
        Data myData;

        /* construction. */
    public:
            /*!
             * @brief Initializes the description using a unique name.
             */
        Class ( const string& name );

        /* methods. */
    public:
        const Data& get () const {
            return (myData);
        }

        const string& name () const {
            return (myName);
        }

        void instance ( const w32::Module& module ) {
            myData.hInstance = module.handle();
        }

        void eventProcedure ( ::WNDPROC value ) {
            myData.lpfnWndProc = value;
        }

        void cursor ( const Cursor& value ) {
            myData.hCursor = value.handle();
        }

        void backgroundBrush ( const Brush& value ) {
            myData.hbrBackground = value.handle();
        }

        void smallIcon ( const Icon& value ) {
            myData.hIconSm = value.handle();
        }

        void bigIcon ( const Icon& value ) {
            myData.hIcon = value.handle();
        }

        void menu ( const Resource& value ) {
            myData.lpszMenuName = value.identifier();
        }

        void extraClassMemory ( const std::size_t bytes ) {
            myData.cbClsExtra = int(bytes);
        }

        void extraWindowMemory ( const std::size_t bytes ) {
            myData.cbWndExtra = int(bytes);
        }

        void style ( const Style& value );
    };

        /*!
         * @brief Registers the description for a family of windows.
         *
         * You only need one instance of this class for the entire family
         * even when you have multiple windows from that family.
         */
    class Registration :
        private NotCopyable
    {
        /* nested types. */
    public:
        class Style;

        /* data. */
    private:
        const Class myClass;
        Atom myAtom;

        /* construction. */
    public:
            /*!
             * @brief Register the window class.
             */
        explicit Registration ( const Class& class_ );

            /*!
             * @brief Un-register the window class.
             */
        ~Registration ();

        /* methods. */
    public:
            /*!
             * @brief Obtains the system window class description.
             */
        const Class& class_ () const {
            return (myClass);
        }

            /*!
             * @brief Obtains the window class' atom.
             */
        const Atom& atom () const {
            return (myAtom);
        }
    };

        /*!
         * @brief Style for a familiy of windows.
         */
    class Class::Style
    {
        /* data. */
    private:
        ::UINT myFlags;

        /* construction. */
    public:
        Style ()
            : myFlags(0)
        {}

        /* methods. */
    public:
        const ::UINT& get () const {
            return (myFlags);
        }

        void byteAlignClient () {
            myFlags |= CS_BYTEALIGNCLIENT;
        }

        void byteAlignWindow () {
            myFlags |= CS_BYTEALIGNWINDOW;
        }

        void sharedDeviceContext () {
            myFlags |= CS_CLASSDC;
        }

        void receiveDoubleClicks () {
            myFlags |= CS_DBLCLKS;
        }

        #if (MICROSOFT_WINDOWS >= MICROSOFT_WINDOWS_2000)
            void dropShadow () {
                myFlags |= CS_DROPSHADOW;
            }
        #endif /* (MICROSOFT_WINDOWS >= MICROSOFT_WINDOWS_2000) */

        void applicationGlobalClass () {
            myFlags |= CS_GLOBALCLASS;
        }

            /*!
             * @brief Requests the window to be redrawn if the width changes.
             */
        void horizontalRedraw () {
            myFlags |= CS_HREDRAW;
        }

        void noClose () {
            myFlags |= CS_NOCLOSE;
        }

        void privateDeviceContext () {
            myFlags |= CS_OWNDC;
        }

            /*!
             * @brief Allows the window to draw on it's parent.
             *
             * This usually improves performance because the window receives a
             * device context from the system cache.
             */
        void drawOnParent () {
            myFlags |= CS_PARENTDC;
        }

        void doubleBufferred () {
            myFlags |= CS_SAVEBITS;
        }

            /*!
             * @brief Requests the window to be redrawn if the height changes.
             */
        void verticalRedraw () {
            myFlags |= CS_HREDRAW;
        }
    };

} }

#endif /* _w32_gdi_NewClass_hpp__ */
