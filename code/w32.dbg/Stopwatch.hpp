#ifndef _w32_dbg_Stopwatch_hpp__
#define _w32_dbg_Stopwatch_hpp__

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
#include <w32/types.hpp>

namespace w32 {

    class Delta;

}

namespace w32 { namespace dbg {

    //! @addtogroup w32-dbg
    //! @{

    /*!
     * @brief High-resolution performance counter.
     */
    class Stopwatch
    {
        /* data. */
    private:
        int64 myFrequency;
        int64 myReference;

        /* construction. */
    public:
        /*!
         * @brief Create a stopwatch and establish the reference time.
         *
         * @see reset()
         */
        Stopwatch ();

        /* methods. */
    public:
        /*!
         * @brief Reset the stopwatch's reference time.
         * @return Time elapsed since the previous call to @c reset().
         */
        Delta reset ();

        /*!
         * @brief Read the time elapsed since the reference time.
         * @return Time elapsed since the previous call to @c reset().
         */
        Delta read () const;
    };

    //! @}

} }

#endif /* _w32_dbg_Stopwatch_hpp__ */
