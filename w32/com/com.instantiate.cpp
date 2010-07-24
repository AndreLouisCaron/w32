/*!
 * @file com/com.instantiate.cpp
 * @author Andre Caron
 *
 * @brief Utility to check if a COM object is well registered.
 */

#include <com/com.hpp>
#include <win/shl/ext.hpp>
#include <w32/w32.hpp>
#include <iostream>

    // Define interface identifier.
template<> inline com::Guid
    com::guidof< ::IUnknown > () { return (IID_IUnknown); }

namespace {

    template<typename Interface>
    com::Ptr< Interface > instantiate ( const com::Guid& guid )
    {
        Interface * object = 0;
        const com::Result result = ::CoCreateInstance(
            guid, 0, CLSCTX_INPROC_SERVER,
            com::guidof< Interface >(),
            reinterpret_cast<void**>(&object)
            );
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(<>,CoCreateInstance,result);
        }
        return (com::Ptr< Interface >(object));
    }

#if 1
    const com::Guid guid(
        0x8a649db1,0x56cd,0x4640,0x8e,0xfe,0x67,0x0c,0xfc,0x20,0x67,0x0c
        ); // {8A649DB1-56CD-4640-8EFE-670CFC20670C}
#else
    const com::Guid guid(
        0x7b280b72,0xb570,0x41ac,0x8a,0x6e,0xee,0xbc,0x97,0xdc,0xe3,0x7b
        ); //{7B280B72-B570-41AC-8A6E-EEBC97DCE37B}
#endif

}

#include <w32/console-program.hpp>

namespace {

    int run ( int, wchar_t ** )
    try
    {
        const com::Context _(com::ThreadModel::appartment());
        const com::Ptr< ::IUnknown > sheet = 
            ::instantiate< ::IUnknown >(::guid);
        return (EXIT_SUCCESS);
    }
    catch ( const com::UncheckedError& error )
    {
        std::cerr << error.what() << std::endl;
        return (EXIT_FAILURE);
    }

}

#include <w32/console-program.cpp>
