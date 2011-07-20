// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.com.hpp>
#include <w32.shl.ext.hpp>

    // Too lazy, even to re-use!
#include "../ftp-client/ftp.hpp"
#include "../ftp-client/ftp.cpp"

namespace {

    class Extension :
        public w32::shl::ext::Namespace
    {
        /* class data. */
    public:
        static const w32::com::Guid guid;

        /* data. */
    private:
        long myReferenceCount;

        /* construction. */
    public:
        Extension ()
            : myReferenceCount(1)
        {
            w32::gdi::messagebox(L"namespace-ftp", L"inside!");
        }

        /* overrides. */
    public:
            // Allow IPersist to return exported class' identifier.
        virtual w32::com::Guid server () const { return (guid); }

            // Standard COM methods.
        virtual w32::ulong __stdcall AddRef () {
            return (::InterlockedIncrement(&myReferenceCount));
        }
        virtual w32::ulong __stdcall Release ()
        {
            if ( ::InterlockedDecrement(&myReferenceCount) == 0 )
            {
                delete this; return (0);
            }
            return (myReferenceCount);
        }
    };

        // This is the unique identifier used to create objects of our class.
    const w32::com::Guid Extension::guid(
        0x5450A57D,0xF5A6,0x42fC,0x87,0xBD,0x7D,0x0F,0xB1,0x9F,0xE9,0xA7
        ); // {5450A57D-F5A6-42fC-87BD-7D0FB19FE9A7}

        // This is the real type of object exposed by the our dynamic library.
    typedef Extension ExportedClass;

}

    // Compile this as a COM in-process server.
#include <w32/com/in-process-server.cpp>

    // Link automagically.
#pragma comment ( lib, "w32.lib" )
#pragma comment ( lib, "w32.com.lib" )
#pragma comment ( lib, "w32.dbg.lib" )
#pragma comment ( lib, "w32.gdi.lib" )
#pragma comment ( lib, "w32.shl.lib" )
#pragma comment ( lib, "w32.shl.ext.lib" )
