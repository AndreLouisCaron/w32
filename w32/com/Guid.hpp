#ifndef _w32_com_Guid_hpp__
#define _w32_com_Guid_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>
#include <iosfwd>

namespace w32{ namespace com {

    class W32_COM_EXPORT Guid
    {
        /* nested types. */
    public:
        typedef ::GUID Value;

        class String;

        /* class data. */
    public:
        static const Guid zero ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        Guid (
            dword a, word b, word c,
            byte d, byte e, byte f, byte g,
            byte h, byte i, byte j, byte k
            );

        Guid ( const Guid& other = zero() );

        Guid ( const Value& value );

        /* methods. */
    public:
        Value& value ();
        const Value& value () const;

        /* operators. */
    public:
        Guid& operator= ( const Guid& other );

        operator const Value& () const;
        bool operator== ( const Guid& other ) const;
        bool operator!= ( const Guid& other ) const;
    };

    W32_COM_EXPORT std::wostream& operator<<
        ( std::wostream& out, const Guid& guid );

    W32_COM_EXPORT std::wistream& operator>>
        ( std::wistream& in, Guid& guid );

    class W32_COM_EXPORT Guid::String
    {
        /* data. */
    private:
        wchar_t myValue[39];

        /* construction. */
    public:
        String ( const Guid& guid );

        /* methods. */
    public:
        const wchar_t * value () const;
    };

    W32_COM_EXPORT std::wostream& operator<<
        ( std::wostream& out, const Guid::String& guid );

        /*!
         * @brief Returns the identifier for a given class/interface.
         *
         * Specialize this function for any class or interface you write or
         * wrap (it is not pre-defined for all classes).
         */
    template<typename Interface> Guid guidof ();

    template<> inline Guid guidof< ::IUnknown > () { return (::IID_IUnknown); }

} }

#endif /* _w32_com_Guid_hpp__ */
