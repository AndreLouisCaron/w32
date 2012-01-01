#ifndef _w32_tp_Queue_hpp__
#define _w32_tp_Queue_hpp__

// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/Timespan.hpp>

namespace w32 { namespace tp {

    class Cleanup;
    class Pool;

    /*!
     * @ingroup w32-tp
     * @brief Dispatch queue for a group of threads.
     */
    class Queue :
        private NotCopyable
    {
        /* nested types. */
    public:
        typedef ::TP_CALLBACK_ENVIRON Data;

        typedef void (__stdcall*Cancel)(void*,void*);

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Queue ( Pool& pool );
        ~Queue ();

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

        void cleanup ( Cleanup& cleanup, Cancel cancel = 0 );
    };

} }

#endif /* _w32_tp_Queue_hpp__ */
