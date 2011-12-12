#ifndef _w32_com_Factory_hpp__
#define _w32_com_Factory_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32.com/Model.hpp>
#include <memory>

namespace w32{ namespace com {

        /*!
         * @brief Implements boiler-plate code for a simple factory.
         */
    template<typename Class>
    class Factory :
        public Model< ::IClassFactory >
    {
        /* methods. */
    public:
        ::HRESULT __stdcall LockServer ( ::BOOL lock ) {
            return (E_NOTIMPL);
        }

        ::HRESULT __stdcall CreateInstance (
            ::IUnknown * object, const ::GUID& guid, void ** output
            );
    };

    template<typename Class>
    ::HRESULT __stdcall Factory<Class>::CreateInstance (
        ::IUnknown * object, const ::GUID& guid, void ** output
        )
    try
    {
        if ( object != 0 ) {
            return (CLASS_E_NOAGGREGATION);
        }
        const Ptr<Class> instance(new Class());
        return (instance->QueryInterface(guid,output));
    }
    catch ( const std::bad_alloc& ) {
        return (E_OUTOFMEMORY);
    }
    catch ( ... ) {
        return (E_FAIL);
    }

} }

template<> inline w32::com::Guid
    w32::com::guidof< ::IClassFactory > ()
{
    return (IID_IClassFactory);
}

#endif /* _w32_com_Factory_hpp__ */
