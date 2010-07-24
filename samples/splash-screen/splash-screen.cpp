// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.hpp>
#include <w32.fs.hpp>
#include <w32.io.hpp>
#include <w32.gdi.hpp>
#include <w32.mt.hpp>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>

namespace {

        // Mediator, handling coordination between widgets.
    class MyApplication :
        public w32::gdi::Application< MyApplication >
    {
        /* data. */
    private:
        w32::gdi::ImageList myImages;
        w32::gdi::TreeView myExplorer;
        w32::gdi::DateTimePicker myPicker;

        /* construction. */
    public:
        MyApplication ()
            : w32::gdi::Application< MyApplication >(*this),
              myImages(w32::gdi::Size(12,12), 2),
              myExplorer(window(), w32::gdi::Rectangle(10, 175, 10, 255)),
              myPicker(window(), w32::gdi::Rectangle(275, 375, 10, 35))
        {
                // Load images.
            myImages.add(w32::gdi::Icon::asterisk());
            myImages.add(w32::gdi::Icon::error());
            
                // ... more configuration ...
            myExplorer.images(myImages);
            w32::gdi::TreeView::Insertion solution;
            solution.caption(L"solution");
            solution.images(0, 1);
            w32::gdi::TreeView::Insertion project(myExplorer.insert(solution));
            project.caption(L"project");
            project.images(0, 1);
            myExplorer.insert(project);
            
            using namespace w32::gdi;
            dispatcher()
                .add(myPicker, DateTimePicker::Change(),
                    make_callback< ::NMDATETIMECHANGE, &MyApplication::myPicker_Change>())
                 ;
            
                // Set some description of what this is...
            window().text(L"My 1st w32++ application.");
            
                // Make the window visible once everything is set up.
            window().show();
            
                // Bring to front... splash screen messes up focus!
            w32::gdi::foreground(window());
        }

        /* methods. */
    private:
        void myPicker_Change ( ::NMDATETIMECHANGE change )
        {
            if ( change.dwFlags == GDT_VALID ) {
                w32::gdi::messagebox(L"myPicker", L"date/time changed 1!");
            }
        }
    };

        // Background thread watching changes in the current directory.
    void watch ( void * context )
    {
            // Usy synchronous calls to list changes.
        w32::mt::ManualResetEvent& done =
            *reinterpret_cast< w32::mt::ManualResetEvent* >(context);
        w32::fs::Changes changes(".", w32::fs::Changes::Filter::all());
        
            // Make handle set for wait notification.
        w32::Waitable::Set handles;
        handles |= changes.handle();
        handles |= done.handle();
        
            // Log all changes until requested to exit.
        for ( ; (w32::Waitable::any(handles) == 0); changes.next() ) {
            std::cout << "Something changed!" << std::endl;
        }
    }

}

#include <w32/gdi/windows-program.hpp>

namespace {

    int run ( const w32::string& command, int )
    {
            // Use the common controls, of course!
        w32::gdi::enable_common_controls();
        
            // Watch changes in the current directory.
        w32::mt::ManualResetEvent done;
        w32::mt::Thread thread(
            w32::mt::Thread::adapt<void,void*,&::watch>(), &done);
        
            // Show a splash screen while loading!
        { w32::gdi::Splash _(L".tests/shiina.bmp");
            
                // Lengthy initialisation...
            w32::mt::sleep(w32::Timespan(1, w32::Timespan::Unit::second()));
        }
        
            // Create an application window.
        ::MyApplication _;
        
            // Process events until the user exits.
        const w32::wparam status = w32::gdi::loop();
        
            // Request thread termination, wait for OK, then report status.
        done.set(); thread.join(); return (status);
    }

}

#include <w32/gdi/windows-program.cpp>

    // Link automagically.
#pragma comment ( lib, "w32.lib" )
#pragma comment ( lib, "w32.dbg.lib" )
#pragma comment ( lib, "w32.fs.lib" )
#pragma comment ( lib, "w32.io.lib" )
#pragma comment ( lib, "w32.gdi.lib" )
#pragma comment ( lib, "w32.mt.lib" )
