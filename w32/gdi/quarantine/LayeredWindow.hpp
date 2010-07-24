#ifndef _win32gdi_LayeredWindow_HPP__
#define _win32gdi_LayeredWindow_HPP__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

    // Needs SERIOUS refactoring.
#if 0

#include "BlendFunction.hpp"
#include "DeviceCompatibleBitmap.hpp"
#include "Window.hpp"
#include <windows.h>

namespace win32gdi {

#if (MICROSOFT_WINDOWS >= MICROSOFT_WINDOWS_2000)

        /*!
         * @brief Double buffered window using transparency effects.
         */
    class LayeredWindow : public Window
    {
        /* nested types. */
    public:
        class Style : public Window::Style
        {
            /* construction. */
        public:
            Style () {
                /*transparent();
                layered();*/
            }
        };

        /* data. */
    private:
        DeviceCompatibleBitmap myBitmap;
        ConstantAlphaBlend myBlend;

        /* construction. */
    public:
        LayeredWindow (
            const Class& wndclass, const Rectangle& bounds, const Style& style
            ) 
            : Window(wndclass,bounds,style),
              myBitmap(DisplayDeviceContext(),bounds.span()),
              myBlend(155)
        {
            ::memset(myBitmap.buffer(),255,myBitmap.info().bufferSize());
        }

        /* methods. */
    public:
            /*!
             * @brief Update the bitmap in the window.
             */
        void update ()
        {
                // Make sur the bitmap reflects the image.
            DeviceCompatibleBitmap::Selection selection(myBitmap);
            myBitmap.commit();

                // Need copies because UpdateLayeredWindow() doesn't declare
                // it's input parameters as const.
            DisplayDeviceContext dstdc;
            ::POINT wndpos = bounds().origin().get();
            ::SIZE wndsize = bounds().span().get();
            ::POINT bmppos = Point(0,0).get();
            ::BLENDFUNCTION blend = myBlend.get();
            const ::BOOL result = ::UpdateLayeredWindow(
                handle().get(), dstdc.handle().get(), &wndpos, &wndsize,
                myBitmap.context().handle().get(), &bmppos, 0, &blend,
                ULW_ALPHA
                );
            if ( result == FALSE ) {
                UNCHECKED_WIN32GDI_ERROR(UpdateLayeredWindow,::GetLastError());
            }
        }
    };

#endif /* (MICROSOFT_WINDOWS >= MICROSOFT_WINDOWS_2000) */

}

#endif

#endif /* _win32gdi_LayeredWindow_HPP__ */
