// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/form.hpp>

#include <w32.gdi.hpp>
#include <exception>
#include <iostream>

#include <w32/gdi/windows-program.hpp>

namespace {

    int run ( const w32::string& )
    {
        Application application;
        Form form(application);
        
        form.window().show();
        
        w32::gdi::ThreadWindowsEvents queue;
        w32::gdi::Event event;
        while ( queue.next(event) ) {
            event.translate();
            event.dispatch();
        }
        return (EXIT_SUCCESS);
    }

}

#include <w32/gdi/windows-program.cpp>
