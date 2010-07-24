#ifndef _win32gdi_CustomCursor_HPP__
#define _win32gdi_CustomCursor_HPP__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "wingdi.hpp"
#include "Cursor.hpp"
#include "UncheckedError.hpp"

namespace win32gdi {

        /*!
	 * @brief Wraps a cursor created at runtime from a bitmap.
         */
    class CustomCursor : public Cursor
    {
        /* nested types. */
    public:
        class Handle : public Cursor::Handle
        {
            /* data. */
        private:
            ::HICON myValue;

            /* construction. */
        public:
            explicit Handle ( ::HICON value )
                : myValue(value)
            {}

            virtual ~Handle () {
                reset();
            }

            /* methods. */
        public:
            virtual ::HCURSOR get () const {
                return ((::HCURSOR)myValue);
            }

            void reset ( ::HICON value = 0 )
            {
                if ( ok() && (::DestroyIcon(myValue) == FALSE) ) {
                    UNCHECKED_WIN32C_ERROR(DestroyIcon,::GetLastError());
                }
                myValue = value;
            }
        };

        class Info : private concepts::NotCopyable
        {
            /* data. */
        private:
            ::ICONINFO myData;

            /* construction. */
        public:
            Info ( const ::POINT & hotspot, ::HBITMAP mask, ::HBITMAP color )
            {
                myData.fIcon = FALSE;
                myData.xHotspot = hotspot.x;
                myData.yHotspot = hotspot.y;
                myData.hbmMask  = mask;
                myData.hbmColor = color;
            }

            /* methods. */
        public:
            ::ICONINFO get () {
                return (myData);
            }

            const ::ICONINFO & get () const {
                return (myData);
            }
        };

        /* data. */
    private:
        Info myInfo;
        Handle myHandle;

        /* construction. */
    public:
            // Create a user defined cursor from bitmaps.
            // Please try out and document this...
        CustomCursor ( ::POINT hotspot, ::HBITMAP mask, ::HBITMAP color )
            : myInfo(hotspot,mask,color),
              myHandle(::CreateIconIndirect(&myInfo.get()))
        {
            if ( myHandle.bad() ) {
                UNCHECKED_WIN32C_ERROR(CreateIconIndirect,::GetLastError());
            }
        }

        /* methods. */
    public:
        virtual const Handle & handle () const {
            return (myHandle);
        }
    };

}

#endif /* _win32gdi_CustomCursor_HPP__ */
