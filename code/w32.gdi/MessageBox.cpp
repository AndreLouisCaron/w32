// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/MessageBox.hpp>
#include <w32/Error.hpp>

namespace {

    int popup ( ::HWND root, ::LPCWSTR text, ::LPCWSTR title, ::UINT type )
    {
        const int result = ::MessageBoxW(root, text, title, type);
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(MessageBox,::GetLastError());
        }
        return (result);
    }

}

namespace w32 { namespace gdi {

    const MessageBox::Icon MessageBox::Icon::none(0);
    const MessageBox::Icon MessageBox::Icon::exclamation(MB_ICONEXCLAMATION);
    const MessageBox::Icon MessageBox::Icon::warning(MB_ICONWARNING);
    const MessageBox::Icon MessageBox::Icon::information(MB_ICONINFORMATION);
    const MessageBox::Icon MessageBox::Icon::asterisk(MB_ICONASTERISK);
    const MessageBox::Icon MessageBox::Icon::question(MB_ICONQUESTION);
    const MessageBox::Icon MessageBox::Icon::stop(MB_ICONSTOP);
    const MessageBox::Icon MessageBox::Icon::error(MB_ICONERROR);
    const MessageBox::Icon MessageBox::Icon::hand(MB_ICONHAND);

    MessageBox::Icon::Icon ( Value value )
        : myValue(value)
    {
    }

    MessageBox::Icon::Value MessageBox::Icon::value () const
    {
        return (myValue);
    }

    const MessageBox::Buttons MessageBox::Buttons::abortRetryIgnore(
        MB_ABORTRETRYIGNORE
        );
    const MessageBox::Buttons MessageBox::Buttons::cancelRetryContinue(
        MB_CANCELTRYCONTINUE
        );
    const MessageBox::Buttons MessageBox::Buttons::help(MB_HELP);
    const MessageBox::Buttons MessageBox::Buttons::ok(MB_OK);
    const MessageBox::Buttons MessageBox::Buttons::okCancel(MB_OKCANCEL);
    const MessageBox::Buttons MessageBox::Buttons::retryCancel(MB_RETRYCANCEL);
    const MessageBox::Buttons MessageBox::Buttons::yesNo(MB_YESNO);
    const MessageBox::Buttons MessageBox::Buttons::yesNoCancel(MB_YESNOCANCEL);

    MessageBox::Modality MessageBox::Modality::application (
        const Window& root
        )
    {
        return (Modality(MB_APPLMODAL, root.handle()));
    }

    MessageBox::Modality MessageBox::Modality::system ( const Window& root )
    {
        return (Modality(MB_SYSTEMMODAL, root.handle()));
    }

    MessageBox::Modality MessageBox::Modality::task ()
    {
        return (Modality(MB_TASKMODAL,0));
    }

    MessageBox::Result MessageBox::show ( const string& message )
    {
        return (Result(popup(
            0, L"", message.c_str(), 0
            )));
    }

    void messagebox ( const string& title, const string& message )
    {
        ::MessageBoxW(0, message.c_str(), title.c_str(), MB_ICONERROR);
    }

} }
