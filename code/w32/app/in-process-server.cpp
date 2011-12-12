/*!
 * @file com/in-process-server.cpp
 * @author Andre Caron
 *
 * @brief Boiler-plate code for an in-process COM server.
 *
 * @todo Add automatic registration code, with a minimal customization.
 */

#include <w32/app/in-process-server.hpp>

extern "C" {

    ::ULONG __stdcall DllMain (
        ::HINSTANCE instance, ::DWORD reason, ::LPVOID reserved
        )
    try
    {
        if ( reason == DLL_PROCESS_ATTACH )
        {
            ::GlobalObjectCount = 0;
        }
        else if ( reason == DLL_PROCESS_DETACH )
        {
            if ( ::GlobalObjectCount > 0 ) {}
        }
        return (TRUE);
    }
    catch ( ... ) {
        return (FALSE);
    }

    ::HRESULT __stdcall DllCanUnloadNow ()
    try
    {
        return ((GlobalObjectCount <= 0)? S_OK : S_FALSE);
    }
    catch ( ... ) {
        return (S_FALSE);
    }

    ::HRESULT __stdcall DllGetClassObject (
        const ::GUID& class_, const ::GUID& interface_, void ** object
        )
    try
    {
        if ( object == 0 ) {
            return (E_POINTER);
        }
        (*object) = 0;
        
        if ( w32::com::Guid(class_) == ExportedClass::guid )
        {
            const w32::com::Ptr< ::IClassFactory > factory(
                new w32::com::Factory< ExportedClass >()
                );
            return (factory->QueryInterface(interface_,object));
        }
        
        return (CLASS_E_CLASSNOTAVAILABLE);
    }
    catch ( const std::bad_alloc& ) {
        return (E_OUTOFMEMORY);
    }
    catch ( ... ) {
        return (E_FAIL);
    }

    volatile ::LONG GlobalObjectCount = 0;

}

// Override operator new() to force use of COM allocator.

/*
#pragma warning ( disable : 4290 )

void * operator new ( size_t size ) throw (std::bad_alloc)
{
    void *const block = ::CoTaskMemAlloc(size);
    if ( block == 0 ) {
        throw (std::bad_alloc());
    }
    return (block);
}

void * operator new ( size_t size, const std::nothrow_t& ) throw()
{
    return (::CoTaskMemAlloc(size));
}

void operator delete ( void * block, size_t ) throw()
{
    ::CoTaskMemFree(block);
}
*/
