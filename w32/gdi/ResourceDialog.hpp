#ifndef _win32c_gdi_ResourceDialog_hpp__
#define _win32c_gdi_ResourceDialog_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "../Resource.hpp"
#include "Dialog.hpp"
#include <Windows.h>

namespace win32c { namespace gdi {

    class ResourceDialog : public Dialog
    {
        /* nested types. */
    public:
        class Handle : public Dialog::Handle
        {
            /* data. */
        private:
            ::HWND myValue;

            /* construction. */
        public:
            explicit Handle ( ::HWND value )
                : myValue(value)
            {}

            virtual ~Handle ()
            {
                if ( ok() && (::DestroyWindow(myValue) == FALSE)) {
                    ::UNCHECKED_WIN32C_ERROR(DestroyWindow,::GetLastError());
                }
                myValue = 0;
            }

            /* methods. */
        public:
            virtual ::HWND get () const {
                return (myValue);
            }
        };

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        ResourceDialog ( const Resource& resource )
            : myHandle(::CreateDialog(
                  resource.module(), resource.name(), 0, &::DefDlgProc
                  ))
        {
            if ( myHandle.bad() ) {
                UNCHECKED_WIN32C_ERROR(CreateDialog,::GetLastError());
            }
        }
    };

} }

#endif /* _win32c_gdi_ResourceDialog_hpp__ */
