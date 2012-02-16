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
