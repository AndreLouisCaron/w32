#ifndef _w32_dbg_Log_hpp__
#define _w32_dbg_Log_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/Reference.hpp>
#include <w32/string.hpp>
#include <w32/dbg/Event.hpp>

namespace w32 { namespace dbg {

    class W32_DBG_EXPORT Log
    {
        /* nested types. */
    public:
        typedef Reference< ::HANDLE, void(*)(::HANDLE) > Handle;

        /* class methods. */
    public:
        static Handle claim ( ::HANDLE object );
        static Handle proxy ( ::HANDLE object );

        static void install (
            const string& name, const string& path,
            const string& categories, dword count );

        static void remove ( const string& name );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    protected:
        explicit Log ( const Handle& handle );

    public:
        Log ( const string& name );

        /* methods. */
    public:
        const Handle& handle () const;
        void report ( const Event& event );
    };

} }

#endif /* _w32_dbg_Log_hpp__ */
