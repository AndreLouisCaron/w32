#ifndef _w32_dbg_Event_hpp__
#define _w32_dbg_Event_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/types.hpp>

namespace w32 { namespace dbg {

    class W32_DBG_EXPORT Event
    {
        /* nested types. */
    public:
        class Type;
        typedef word Category;
        typedef dword Message;

        /* construction. */
    public:
        virtual ~Event () {
        }

        /* methods. */
    public:
        virtual Type type () const = 0;
        virtual Message message () const = 0;

        virtual Category category () const {
            return (Category(0));
        }

        virtual word argc () const {
            return (0);
        }

        virtual const wchar_t ** argv () const {
            return (0);
        }
    };

    class W32_DBG_EXPORT Event::Type
    {
        /* class data. */
    public:
        static const Type success ();
        static const Type error ();
        static const Type warning ();
        static const Type information ();
        static const Type auditsuccess ();
        static const Type auditfailure ();
        static const Type all ();

        /* nested types. */
    public:
        typedef word Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Type ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        operator Value () const;
    };


} }

#endif /* _w32_dbg_Event_hpp__ */
