#ifndef _w32_ts2_Handler_hpp__
#define _w32_ts2_Handler_hpp__

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

namespace w32 { namespace ts {

        /*!
         * @brief COM local server object to implement for custom actions.
         *
         * If you wish to perform some action that was not thought of by the
         * guys at Microsoft who designed the API, you can implement custom-made
         * actions yourself to extend the default set.
         *
         * These actions are implemented via COM local servers.
         *
         * @note Your COM server should be compiled for multi-threading.
         * @warning The installation of the COM server absolutely needs the
         *    'DllSurrogate' value or the creation of your object will fail.
         */
    class Handler :
        public com::Model< ::ITaskHandler >
    {
        /* nested types. */
    public:
        class Status;

        /* construction. */
    private:
        Handler ( const Handler& );

        /* methods. */
    private:
        virtual void start ( Status& status, const bstring& data ) = 0;

        /* overrides. */
    public:
        virtual ::HRESULT __stdcall Start
            ( ::IUnknown* scheduler, ::BSTR data );
        virtual ::HRESULT __stdcall Stop ( ::HRESULT * result );
        virtual ::HRESULT __stdcall Pause ();
        virtual ::HRESULT __stdcall Resume ();
    };

        /*!
         * @brief Allows the task to inform the task scheduler about its
         *    completion.
         */
    class Handler::Status :
        public com::Wrapper< ::ITaskHandlerStatus >
    {
        /* construction. */
    public:
        explicit Status ( ::ITaskHandlerStatus * object )
            : com::Wrapper< ::ITaskHandlerStatus >(object)
        {}

        /* methods. */
    public:
            /*!
             * @brief Indicates that the action has successfully completed.
             *
             * @note If you wish to return some kind of status code to the
             *    task scheduler, you should call the appropriate overload.
             */
        void completed () {
            completed(com::Result::success());
        }

            /*!
             * @brief Indicates that the action has completed.
             *
             * @param status Status code to return to the task scheduler. If
             *    you wish to indicate success, you should call the
             *    parameterless version overload instead.
             */
        void completed ( com::Result status );

            /*!
             * @brief Indicates that the action is partially complete.
             *
             * This is useful for actions that take some time to run.
             *
             * @param percentage Estimate of the amount of work completed.
             * @param message Progress message to display.
             */
        void status ( short percentage, const bstring& message );
    };

} }

template<> inline w32::com::Guid
    w32::com::guidof< ::ITaskHandler > ()
{
    return (IID_ITaskHandler);
}

template<> inline w32::com::Guid
    w32::com::guidof< ::ITaskHandlerStatus > ()
{
    return (IID_ITaskHandlerStatus);
}

#endif /* _w32_ts2_Handler_hpp__ */
