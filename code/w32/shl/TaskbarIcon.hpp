#ifndef _w32_shl_TaskbarIcon_hpp__
#define _w32_shl_TaskbarIcon_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32.gdi.hpp>

namespace w32 { namespace shl {

    class TaskbarIcon
    {
        /* nested types. */
    public:
        typedef uint Identifier;
        typedef uint Message;
        typedef w32::gdi::Window Window;
        typedef w32::gdi::Icon Image;

        typedef ::NOTIFYICONDATAA Data;

        /* class methods. */
    public:
        static Message creation ();

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        TaskbarIcon ( const Window& window, Identifier identifier );

        /* class methods. */
    public:
        static void add ( TaskbarIcon& icon );
        static void remove ( TaskbarIcon& icon );

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;
        void message ( Message value );
        void tooltip ( const char * text );
        void image ( const Image& image );
    };

} }

#endif /* _w32_shl_TaskbarIcon_hpp__ */
