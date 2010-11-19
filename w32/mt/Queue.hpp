#ifndef _w32_mt_Queue_hpp__
#define _w32_mt_Queue_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/Timespan.hpp>

namespace w32 { namespace mt {

    class Cleanup;
    class Pool;

    class W32_MT_EXPORT Queue :
        private NotCopyable
    {
        /* nested types. */
    public:
        typedef ::TP_CALLBACK_ENVIRON Data;

        typedef void(__stdcall*Work)
            (::PTP_CALLBACK_INSTANCE,::PVOID,::PTP_WORK);

        typedef void(__stdcall*Timer)
            (::PTP_CALLBACK_INSTANCE,::PVOID,::PTP_TIMER);

        typedef void(__stdcall*Cancel)(::PVOID,::PVOID);

        template<typename A, void(*F)(A)>
        struct adapt;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Queue ();
        ~Queue ();

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

        void pool ( Pool& pool );
        void cleanup ( Cleanup& cleanup, Cancel cancel = 0 );

        void submit ( Work work, void * context = 0 );
        void submit ( Timer work, const Timespan& delai, void * context = 0 );
    };

        // "Full-fledged" case.
    template<void(*F)(void*)>
    struct Queue::adapt<void*,F>
    {
        operator Queue::Work () const {
            return (work);
        }
        operator Queue::Timer () const {
            return (timer);
        }
    private:
            // Actual implementation.
        static void __stdcall work
            ( ::PTP_CALLBACK_INSTANCE, ::LPVOID p, ::PTP_WORK )
        {
            return (F(p));
        }
        static void __stdcall timer
            ( ::PTP_CALLBACK_INSTANCE, ::LPVOID p, ::PTP_TIMER )
        {
            return (F(p));
        }
    };

        // Simple case.
    template<void(*F)()>
    struct Queue::adapt<void,F>
    {
        operator Queue::Work () const {
            return (work);
        }
        operator Queue::Timer () const {
            return (timer);
        }
    private:
            // Actual implementation.
        static void __stdcall work
            ( ::PTP_CALLBACK_INSTANCE, ::LPVOID, ::PTP_WORK )
        {
            return (F());
        }
        static void __stdcall timer
            ( ::PTP_CALLBACK_INSTANCE, ::LPVOID, ::PTP_TIMER )
        {
            return (F());
        }
    };

} }

#endif /* _w32_mt_Queue_hpp__ */
