#ifndef _w32_com_Result_hpp__
#define _w32_com_Result_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32{ namespace com {

    class W32_COM_EXPORT Result
    {
        /* nested types. */
    public:
        typedef ::HRESULT Value;

        /* class data. */
    public:
        static const Result success ();
        static const Result failure ();
        static const Result invalid ();
        static const Result false_ ();
        static const Result outofmemory ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        Result ( Value value = 0 )
            : myValue(value)
        {}

        /* methods. */
    public:
        bool good () const {
            return (SUCCEEDED(myValue));
        }

        bool bad () const {
            return (!good());
        }

        Value value () const {
            return (myValue);
        }

        /* operators. */
    public:
        Result& operator= ( ::HRESULT value )
        {
            myValue = value;
            return (*this);
        }

        operator Value () const {
            return (value());
        }

        operator bool () const {
            return (good());
        }

        bool operator! () const {
            return (bad());
        }

        bool operator== ( const Result& other ) const {
            return (myValue == other.myValue);
        }

        bool operator!= ( const Result& other ) const {
            return (myValue != other.myValue);
        }
    };

} }

#endif /* _w32_com_Result_hpp__ */
