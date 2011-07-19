#ifndef _w32_ipc_Processes_hpp__
#define _w32_ipc_Processes_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/Object.hpp>
#include <w32/ipc/Process.hpp>

namespace w32 { namespace ipc {

    class Processes :
        public Object
    {
        /* nested types. */
    public:
        class Entry;

        /* construction. */
    public:
        Processes ();

        /* methods. */
    public:
        bool find ( Entry& entry );
        bool next ( Entry& entry );
    };

    class Processes::Entry
    {
        /* nested types. */
    public:
        typedef ::PROCESSENTRY32W Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Entry ();

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

        void clear ();

        const Process self () const;
        const Process parent () const;
        const dword threads () const;
        const string executable () const;
    };

} }

#endif /* _w32_ipc_Processes_hpp__ */
