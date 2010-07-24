#ifndef _win32c_com_String_hpp__
#define _win32c_com_String_hpp__

/*!
 * @file String.hpp
 * @author Andre Caron
 */

#include "../NotCopyable.hpp"
#include "UncheckedError.hpp"
#include <string>
#include <ShlWApi.h>
#include <ShObjIdl.h>
#include <Windows.h>

namespace win32c { namespace com {

        /*!
         * @brief Hold COM string buffer.
         */
    class String :
        private NotCopyable
    {
        /* class methods. */
    private:
        wchar_t * extract ( const ::ITEMIDLIST * path, ::STRRET& input )
        {
            if ( input.uType == STRRET_CSTR )
            {
                const size_t length = ( path->mkid.cb - input.uOffset );
                const char *const source = input.cStr;
                wchar_t *const output = (wchar_t*)::CoTaskMemAlloc(2*(length+1));
                size_t count = 0;
                ::mbstowcs_s(&count,output,length,source,_TRUNCATE);
                output[length] = L'\0';
                return (output);
            }
            else if ( input.uType == STRRET_OFFSET )
            {
                const size_t length = ( path->mkid.cb - input.uOffset );
                const wchar_t *const source = (const wchar_t*)
                    ( ((const ::BYTE*)path) + input.uOffset );
                wchar_t *const output = (wchar_t*)::CoTaskMemAlloc(length+2);
                ::wcsncpy_s(output,length/2,source,_TRUNCATE);
                output[length] = L'\0';
                return (output);
            }
            else if ( input.uType == STRRET_WSTR ) {
                return (input.pOleStr);
            }
#if 0 // StrRetToStr() apparently doesn't work!
            wchar_t * output = 0;
            const Result result = ::StrRetToStrW(&input,path,&output);
            if ( result.bad() ) {
                UNCHECKED_COM_ERROR(windows,StrRetToStr,result);
            }
            return (output);
#endif
            return (0);
        }

        /* data. */
    private:
        wchar_t * myPtr;

        /* construction. */
    public:
        explicit String ( wchar_t * ptr = 0 )
            : myPtr(ptr)
        {}

        explicit String ( const ::ITEMIDLIST * path, ::STRRET& data )
            : myPtr(extract(path,data))
        {}

        ~String ()
        {
            if ( ok() ) {
                ::CoTaskMemFree(myPtr);
            }
        }

        /* methods. */
    public:
        bool ok () const {
            return (myPtr != 0);
        }

        const wchar_t * c_str () const {
            return (myPtr);
        }

        operator std::wstring () const
        {
            return (std::wstring(ok()? myPtr : L""));
        }
    };

    inline std::wostream & operator<<
        ( std::wostream & out, const String& value )
    {
        return (out << value.c_str());
    }

} }

#endif /* _win32c_com_String_hpp__ */
