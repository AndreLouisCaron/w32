// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.shl/Binding.hpp>
#include <w32.com/Error.hpp>

namespace {

    ::IBindCtx * allocate ()
    {
        ::IBindCtx * binding = 0;
        const w32::com::Result result = ::CreateBindCtx(0, &binding);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(none, CreateBindCtx, result);
        }
        return (binding);
    }

}

namespace w32 { namespace shl {

    Binding::Binding ()
        : com::Wrapper< ::IBindCtx >( ::allocate() )
    {
    }

    Binding::Options Binding::options () const
    {
        Options options;
        const com::Result result = ptr()->GetBindOptions(&options.data());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IBindCtx, GetBindOptions, result);
        }
        return (options);
    }

    void Binding::options ( const Options& options )
    {
        const com::Result result =
            ptr()->SetBindOptions(const_cast< ::BIND_OPTS* >(&options.data()));
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IBindCtx, SetBindOptions, result);
        }
    }

    Binding::Options::Options ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.cbStruct = sizeof(myData);
    }

    Binding::Options::Data& Binding::Options::data ()
    {
        return (myData);
    }

    const Binding::Options::Data& Binding::Options::data () const
    {
        return (myData);
    }

    void Binding::Options::access ( dword access )
    {
        myData.grfMode = access;
    }

} }
