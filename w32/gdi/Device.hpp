#ifndef _w32_gdi_Device_hpp__
#define _w32_gdi_Device_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <vector>

namespace w32 {

    class string;

}

namespace w32 { namespace gdi {

        /*!
         * @brief Display device information.
         */
    class W32_GDI_EXPORT Device
    {
        /* nested types. */
    public:
        typedef ::DISPLAY_DEVICEW Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        explicit Device ( const Data& data );
        explicit Device ( const string& name );

        /* methods. */
    public:
        string name () const;
        string description () const;
        string identifier () const;
        string key () const;

        bool desktop () const;
        bool primary () const;
        bool removable () const;
        bool mirroring () const;
    };

        /*!
         * @brief Enumerates display devices.
         *
         * @param op Function object invoked for every display device.
         */
    template<typename Op>
    void devices ( Op op )
    {
        ::DISPLAY_DEVICEW data;
        ::ZeroMemory(&data, sizeof(data));
        data.cb = sizeof(data);
        
        ::DWORD i = 0;
        while ( ::EnumDisplayDevicesW(0, i++, &data, 0) != FALSE ) {
            op(Device(data));
        }
    }

        /*!
         * @brief Enumerates display devices.
         * @return A list of all display devices.
         */
    W32_GDI_EXPORT std::vector< Device > devices ();

} }

#endif /* _w32_gdi_Device_hpp__ */
