#ifndef _w32_in_IStream_hpp__
#define _w32_in_IStream_hpp__

// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Reference.hpp>
#include <w32/string.hpp>
#include <w32/types.hpp>

namespace w32 { namespace in {

    class Session;

    /*!
     * @ingroup w32-in
     * @brief
     */
    class IStream
    {
        /* nested types. */
    public:
        typedef Reference< ::HINTERNET > Handle;

        /* class methods. */
    public:
        static const Handle claim ( ::HINTERNET object );
        static const Handle proxy ( ::HINTERNET object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        IStream ( Session& session, const string& url );

        /* methods. */
    public:
        const Handle& handle () const;

        dword get ( void * data, dword size );
    };

} }

#endif /* _w32_in_IStream_hpp__ */
