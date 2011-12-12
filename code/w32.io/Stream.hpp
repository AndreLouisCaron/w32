#ifndef _w32_io_Stream_hpp__
#define _w32_io_Stream_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Object.hpp>

namespace w32 { namespace io {

        /*!
         * @brief Base class for input/output streams.
         *
         * Provides access to the stream's handle, for low-level manipulation.
         */
    class Stream :
        public Object
    {
        /* nested types. */
    public:
        class Position;
        class Size;
        class Type;

        /* construction. */
    public:
        explicit Stream ( const Handle& handle );

         /* methods. */
     public:
        Size size () const;
        Position position () const;
        void position ( const Position& value ) const;
     };

    class Stream::Type
    {
        /* nested types. */
    public:
        typedef ::DWORD Value;

        /* class data. */
    public:
        static const Type character ();
        static const Type disk ();
        static const Type remote ();
        static const Type ipc ();
        static const Type unknown ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Type ( Value value );

        /* class methods. */
    public:
        static Type of ( const Stream& stream );

        /* methods. */
    public:
        Value value () const;
    };

    class Stream::Position
    {
        /* nested types. */
    public:
        typedef ::LARGE_INTEGER Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        Position ( const Value& value )
            : myValue(value)
        {}

        /* methods. */
    public:
        Value value () const {
            return (myValue);
        }
    };

    class Stream::Size
    {
        /* nested types. */
    public:
        typedef ::LARGE_INTEGER Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        Size ( const Value& value )
            : myValue(value)
        {}

        /* methods. */
    public:
        Value value () const {
            return (myValue);
        }
    };

} }

#endif /* _w32_io_Stream_hpp__ */
