/*!
 * @file w32.net.irda/DeviceSearch.cpp
 * @author Andre Caron
 */

#include <w32.net.irda/DeviceSearch.hpp>
#include <w32/Error.hpp>

// http://msdn.microsoft.com/en-us/library/ms738544(VS.85).aspx

namespace {

    // Computs size (in bytes) of "extended" array.
    int size ( int count ) {
        return (sizeof(::DEVICELIST)+((count-1)*sizeof(::IRDA_DEVICE_INFO)));
    }

    // Allocate "extensible" array.
    ::DEVICELIST * allocate ( int size ) {
        return (static_cast<::DEVICELIST*>(operator new(size)));
    }

    // Fetch size of structure to allocate.
    int count ( ::SOCKET engine )
    {
        int count = 0;
        const int result = ::getsockopt(
                               engine, SOL_IRLMP, IRLMP_ENUMDEVICES, 0, &count
                           );
        if ( result == SOCKET_ERROR ) {
            UNCHECKED_WIN32C_ERROR(getsockopt,::WSAGetLastError());
        }
        return (count);
    }

    const ::DEVICELIST * search ()
    {
        const ::SOCKET engine = ::socket(AF_IRDA, SOCK_STREAM, 0);
        if ( engine == INVALID_SOCKET )
        {
            const int error = ::WSAGetLastError();
            // May return WSAENETDOWN to indicate no IrDA support.
            UNCHECKED_WIN32C_ERROR(socket, error);
        }

        // Get a list of proper size.
        int length = size(count(engine));
        ::DEVICELIST *const list = allocate(length);

        const int result = ::getsockopt(
                               engine, SOL_IRLMP, IRLMP_ENUMDEVICES, (char*)list, &length
                           );
        if ( result == SOCKET_ERROR ) {
            UNCHECKED_WIN32C_ERROR(getsockopt,::WSAGetLastError());
        }

        return (list);
    }

}

namespace w32 {
    namespace net {
        namespace irda {

            DeviceSearch::DeviceSearch ()
                : myDevices(search())
            {
            }

            DeviceSearch::~DeviceSearch ()
            {
                operator delete(myDevices);
            }

        }
    }
}
