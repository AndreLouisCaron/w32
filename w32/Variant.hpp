#ifndef _w32_Variant_hpp__
#define _w32_Variant_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/bstring.hpp>
#include <w32/astring.hpp>
#include <w32/string.hpp>
#include <w32/types.hpp>

namespace w32 {

    /*!
     * @brief Wrapper for common manipulations of the variant structure.
     *
     * The variant structure is a hideous beast: it is a blunt substitute
     * for a generic object type and can hold many different types of
     * values. However, it can only hold one of these at once.
     */
    class Variant
    {
        /* nested types. */
    public:
        typedef ::VARIANT Value;

        class Type;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        Variant ();
        template<typename T> inline
        Variant ( const T& value )
        {
            ::VariantInit(&myValue);
            (*this) = value;
        }

        Variant ( const Value& value );
        Variant ( const Variant& rhs );
        Variant ( const Variant& rhs, const Type& type );
        ~Variant ();

        /* methods. */
    public:
        Value& value ();
        const Value& value () const;

        void clear ();
        void coerce ( const Type& type );
        Type type () const;

        /* operators. */
    public:
        Variant& operator= ( const Variant& rhs );
        Variant& operator= ( bool value );
        Variant& operator= ( int value );
        Variant& operator= ( const bstring& value );
        Variant& operator= ( const astring& value );
        Variant& operator= ( const string& value );
        Variant& operator= ( const std::string& value );
        Variant& operator= ( const std::wstring& value );
        Variant& operator= ( ::IUnknown * value );
        Variant& operator= ( ::BSTR value );

        operator bstring () const;
        operator int32 () const;
    };

    class Variant::Type
    {
        /* nested types. */
    public:
        typedef ::VARTYPE Value;

        /* class data. */
    public:
        static const Type empty ();
        static const Type null ();
        static const Type boolean ();
        static const Type integer ();
        static const Type result ();
        //static const Type bstring ();
        //static const Type astring ();
        static const Type string ();
        static const Type iunknown ();

        /* class methods. */
    public:
        static Type of ( const Variant& variant );

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
            // For internal use only.
        Type ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        operator Value () const;

        bool operator== ( const Type& other ) const;
        bool operator!= ( const Type& other ) const;
    };

}

#endif /* _w32_Variant_hpp__ */
