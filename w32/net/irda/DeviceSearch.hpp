#ifndef _w32_net_irda_DeviceSearch_hpp__
#define _w32_net_irda_DeviceSearch_hpp__

/*!
 * @file w32/net/irda/DeviceSearch.hpp
 * @author Andre Caron
 */

#include <w32/NotCopyable.hpp>
#include <w32/net/irda.hpp>

namespace w32 { namespace net { namespace irda {

    class DeviceSearch :
        private NotCopyable
    {
        /* data. */
    private:
        ::DEVICELIST *const myDevices;

        /* construction. */
    public:
        DeviceSearch ();
        ~DeviceSearch ();

        /* methods. */
    public:
    };

} } }

#endif /* _w32_net_irda_DeviceSearch_hpp__ */
