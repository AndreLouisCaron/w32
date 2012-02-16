#ifndef _w32_gdi_Device_hpp__
#define _w32_gdi_Device_hpp__

// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "__configure__.hpp"
#include <vector>

namespace w32 {

    class string;

}

namespace w32 { namespace gdi {

        /*!
         * @brief Display device information.
         */
    class Device
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
    std::vector< Device > devices ();

} }

#endif /* _w32_gdi_Device_hpp__ */
