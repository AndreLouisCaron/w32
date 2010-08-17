#ifndef _w32_gdi_callback_hpp__
#define _w32_gdi_callback_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace gdi {

        // Placeholder for conversion to universal event handler.
        // Tries to preserve the argument type for compile-time
        // validation against the Notification<> argument type.
    template<class M, class A>
    class delegate
    {
    protected:
            // Universal function prototype.
        typedef void(*backend)(M&,const ::NMHDR*);
    private:
        backend myBackend;
    protected:
            // Base classes provide callback function.
        delegate ( backend function ) : myBackend(function) {}
    public:
        operator backend () const { return (myBackend); }
    };

        // Generic case for a real callback.
    template<class M, class A, void(M::*F)(A)>
    struct callback;

        // Specific case for a WM_NOTIFY handler.
    template<class M, class A, void(M::*F)(A)>
    class callback<M, A, F> : public delegate< M, A >
    {
        static void function ( M& m, const ::NMHDR * h )
        {
            (m.*F)(*reinterpret_cast<const A*>(h));
        }
    public:
        callback () : delegate<M,A>(&function) {}
    };

        // Specific case for a WM_COMMAND handler.
    template<class M, void(M::*F)()>
    class callback<M, void, F> : public delegate< M, void >
    {
        static void function ( M& m, const ::NMHDR * h )
        {
            (m.*F)();
        }
    public:
        callback () : delegate<M,void>(&function) {}
    };

} }

#endif /* _w32_gdi_callback_hpp__ */
