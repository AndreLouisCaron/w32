// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
