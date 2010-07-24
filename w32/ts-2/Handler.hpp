#ifndef _w32_ts2_Handler_hpp__
#define _w32_ts2_Handler_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
    class W32_TS2_EXPORT Handler :
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
    class W32_TS2_EXPORT Handler::Status :
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
