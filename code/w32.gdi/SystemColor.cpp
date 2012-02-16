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

#include <w32.gdi/SystemColor.hpp>
#include <w32.gdi/Color.hpp>

namespace w32 { namespace gdi {

    const SystemColor SystemColor::activeBorder ()
    {
        return (COLOR_ACTIVEBORDER);
    }

    const SystemColor SystemColor::activeCaption ()
    {
        return (COLOR_ACTIVECAPTION);
    }

    const SystemColor SystemColor::applicationWorkspace ()
    {
        return (COLOR_APPWORKSPACE);
    }

    const SystemColor SystemColor::buttonFace ()
    {
        return (COLOR_BTNFACE);
    }

    const SystemColor SystemColor::buttonHighlight ()
    {
        return (COLOR_BTNHILIGHT);
    }

    const SystemColor SystemColor::buttonShadow ()
    {
        return (COLOR_BTNSHADOW);
    }

    const SystemColor SystemColor::buttonText ()
    {
        return (COLOR_BTNTEXT);
    }

    const SystemColor SystemColor::captionText ()
    {
        return (COLOR_CAPTIONTEXT);
    }

    const SystemColor SystemColor::desktop ()
    {
        return (COLOR_DESKTOP);
    }

    const SystemColor SystemColor::grayText ()
    {
        return (COLOR_GRAYTEXT);
    }

    const SystemColor SystemColor::highlight ()
    {
        return (COLOR_HIGHLIGHT);
    }

    const SystemColor SystemColor::highlightText ()
    {
        return (COLOR_HIGHLIGHTTEXT);
    }

    const SystemColor SystemColor::hotlight ()
    {
        return (COLOR_HOTLIGHT);
    }

    const SystemColor SystemColor::inactiveBorder ()
    {
        return (COLOR_INACTIVEBORDER);
    }

    const SystemColor SystemColor::inactiveCaption ()
    {
        return (COLOR_INACTIVECAPTION);
    }

    const SystemColor SystemColor::inactiveCaptionText ()
    {
        return (COLOR_INACTIVECAPTIONTEXT);
    }

    const SystemColor SystemColor::tooltipBackground ()
    {
        return (COLOR_INFOBK);
    }

    const SystemColor SystemColor::tooltipText ()
    {
        return (COLOR_INFOTEXT);
    }

    const SystemColor SystemColor::menu ()
    {
        return (COLOR_MENU);
    }

    const SystemColor SystemColor::menuText ()
    {
        return (COLOR_MENUTEXT);
    }

    const SystemColor SystemColor::scrollbar ()
    {
        return (COLOR_SCROLLBAR);
    }

    const SystemColor SystemColor::window ()
    {
        return (COLOR_WINDOW);
    }

    const SystemColor SystemColor::windowFrame ()
    {
        return (COLOR_WINDOWFRAME);
    }

    const SystemColor SystemColor::windowText ()
    {
        return (COLOR_WINDOWTEXT);
    }

    SystemColor::SystemColor ( Value value )
        : myValue(value)
    {
    }

    SystemColor::operator Value () const
    {
        return (myValue);
    }

    SystemColor::operator Color () const
    {
            // On error,this function returns 0 (black),
            // so the the result cannot be validated!
        return (::GetSysColor(myValue));
    }

} }
