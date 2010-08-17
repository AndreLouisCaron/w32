#ifndef _w32_shl_ext_IconHandler_hpp__
#define _w32_shl_ext_IconHandler_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/shl.ext/Extension.hpp>

namespace w32 { namespace shl { namespace ext {

        /*!
         * @brief Shell extension that dynamically assigns icons to items in
         *    the Windows Explorer.
         *
         * If you want to define icon overlays, you should implement the
         * \c IconOverlayHandler class instead.
         */
    class W32_SHL_EXT_EXPORT IconHandler :
        virtual public Extension,
        public ::IPersistFile,
        public ::IExtractIcon
    {
        /* data. */
    private:
        string myFile;

        /* methods. */
    public:
            /*!
             * @brief Obtains the file name for which we want to obtain icons.
             */
        const string& file () const {
            return (myFile);
        }

            /*!
             * @brief Indicates if the icon handler should accept icon requests
             *    for the given file.
             *
             * You can write code that conditionally sets icons depending on
             * file size, contents, attributes, etc. This is a convenient hook
             * for refusing to assign icons to certain files.
             *
             * The default is to accept all files.
             *
             * @see file()
             */
        virtual bool accepts () const {
            return (true);
        }

            /*!
             * @brief Obtains the big icon.
             */
        virtual const w32::Resource& big () = 0;

            /*!
             * @brief Obtains the small icon.
             */
        virtual const w32::Resource& small () = 0;

        /* overrides. */
    public:
        virtual ::HRESULT __stdcall GetIconLocation (
            ::UINT flags, char *, ::UINT, int *, ::UINT * result
            );
        virtual ::HRESULT __stdcall Extract (
            const char *, ::UINT, ::HICON * big, ::HICON * small, ::UINT size
            );

        virtual ::HRESULT __stdcall GetClassID ( ::CLSID * class_ );
        virtual ::HRESULT __stdcall IsDirty ();
        virtual ::HRESULT __stdcall Load (
            const wchar_t * file, ::DWORD mode
            );
        virtual ::HRESULT __stdcall Save(
            const wchar_t * file, ::BOOL remember
            );
        virtual ::HRESULT __stdcall SaveCompleted ( const wchar_t * file );
        virtual ::HRESULT __stdcall GetCurFile ( wchar_t ** file );
    };

} } }

#endif /* _w32_shl_ext_IconHandler_hpp__ */
