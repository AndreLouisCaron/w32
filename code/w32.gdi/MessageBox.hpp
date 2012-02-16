#ifndef _w32_gdi_MessageBox_hpp__
#define _w32_gdi_MessageBox_hpp__

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

#include <w32/string.hpp>
#include <w32.gdi/Window.hpp>

    // Remove <windows.h> macros that conflict with our names.
#ifdef MessageBox
#   undef MessageBox
#endif

namespace w32 { namespace gdi {

    class MessageBox
    {
        /* nested types. */
    public:
        class Icon
        {
            /* nested types. */
        public:
            typedef uint Value;

            /* class data. */
        public:
            static const Icon none;
            static const Icon exclamation;
            static const Icon warning;
            static const Icon information;
            static const Icon asterisk;
            static const Icon question;
            static const Icon stop;
            static const Icon error;
            static const Icon hand;

            /* data. */
        private:
            Value myValue;

            /* construction. */
        private:
            explicit Icon ( Value value );

            /* methods. */
        public:
            Value value () const;
        };

        class Buttons
        {
            /* class data. */
        public:
            static const Buttons abortRetryIgnore;
            static const Buttons cancelRetryContinue;
            static const Buttons help;
            static const Buttons ok;
            static const Buttons okCancel;
            static const Buttons retryCancel;
            static const Buttons yesNo;
            static const Buttons yesNoCancel;

            /* data. */
        private:
            ::UINT myIdentifier;

            /* construction. */
        private:
            explicit Buttons ( ::UINT identifier )
                : myIdentifier(identifier)
            {}

            /* methods. */
        public:
            ::UINT get () const {
                return (myIdentifier);
            }
        };

        class Modality
        {
            /* class data. */
        public:
            static Modality application ( const Window& root );
            static Modality system ( const Window& root );
            static Modality task ();

            /* data. */
        private:
            ::UINT myIdentifier;
            ::HWND myRoot;

            /* construction. */
        private:
            explicit Modality ( ::UINT identifier, ::HWND root )
                : myIdentifier(identifier), myRoot(root)
            {}

            /* methods. */
        public:
            ::UINT get () const {
                return (myIdentifier);
            }

            ::HWND root () const {
                return (myRoot);
            }
        };

        class Result
        {
            // The show() functions create objects of this class.
        friend class MessageBox;

            /* class data. */
        public:
            static const Result abort;
            static const Result cancel;
            static const Result continue_;
            static const Result ignore;
            static const Result no;
            static const Result ok;
            static const Result retry;
            static const Result tryAgain;
            static const Result yes;

            /* data. */
        private:
            int myValue;

            /* construction. */
        private:
            explicit Result ( int value )
                : myValue(value)
            {}

            /* methods. */
        public:
            int value () const {
                return (myValue);
            }

            /* operators. */
        public:
            bool operator== ( const Result& other ) const {
                return (myValue == other.myValue);
            }

            bool operator!= ( const Result& other ) const {
                return (myValue != other.myValue);
            }
        };

        /* construction. */
    public:
        static Result show ( const string& message );
    };

    void messagebox
        ( const string& title, const string& message );

} }

#endif /* _w32_gdi_MessageBox_hpp__ */
