#ifndef _w32_gdi_SystemColor_hpp__
#define _w32_gdi_SystemColor_hpp__

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

namespace w32 { namespace gdi {

    class Color;

        /*!
         * @brief Enumeration of all colors named by the system.
         */
    class SystemColor
    {
        /* nested types. */
    public:
        typedef int Value;

        /* class data. */
    public:
        static const SystemColor activeBorder ();
        static const SystemColor activeCaption ();
        static const SystemColor applicationWorkspace ();
        static const SystemColor buttonFace ();
        static const SystemColor buttonHighlight ();
        static const SystemColor buttonShadow ();
        static const SystemColor buttonText ();
        static const SystemColor captionText ();
        static const SystemColor desktop ();
        static const SystemColor grayText ();
        static const SystemColor highlight ();
        static const SystemColor highlightText ();
        static const SystemColor hotlight ();
        static const SystemColor inactiveBorder ();
        static const SystemColor inactiveCaption ();
        static const SystemColor inactiveCaptionText ();
        static const SystemColor tooltipBackground ();
        static const SystemColor tooltipText ();
        static const SystemColor menu ();
        static const SystemColor menuText ();
        static const SystemColor scrollbar ();
        static const SystemColor window ();
        static const SystemColor windowFrame ();
        static const SystemColor windowText ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
            // For internal use only.
        SystemColor ( Value value );

        /* operators. */
    public:
            /*!
             * @brief Obtains the system color's identifier.
             */
        operator Value () const;

            /*!
             * @brief Obtains the current RGB value of a system color.
             */
        operator Color () const;
  };

} }

#endif /* _w32_gdi_SystemColor_hpp__ */
