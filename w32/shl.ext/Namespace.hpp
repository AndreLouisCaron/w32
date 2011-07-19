#ifndef _w32_shl_ext_Namespace_hpp__
#define _w32_shl_ext_Namespace_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>
#include <w32/shl/Path.hpp>

namespace w32 { namespace shl { namespace ext {

    class Namespace :
        public ::IItemNameLimits,
        public ::IObjectProvider,
        public ::IPersistFolder2,
        public ::IPersistIDList,
        public ::IShellFolder2,
        public ::IStorage
    {
        /* data. */
    private:
        long myReferenceCount;
        Path myRoot;
        Path myPath;

        /* construction. */
    public:

        /* methods. */
    public:
        const Path& root ();
        const Path& path ();

        virtual com::Guid server () const = 0;

            // Allow archive formats and other network-based filesystems
            // to impose limits on names. By default, these are all-pass.
            // [in]validchars() may (and probably should) return statically
            // allocated tables, proper copies are made before returning
            // to the caller.
            //
            // note: this handles path as well as names.
        virtual int maxlength ( const string& path );
        virtual const wchar_t *   validchars ();
        virtual const wchar_t * invalidchars ();

            // Need some kind of lookup based on root-relative path.
        //virtual void lookup ( const string& path ) = 0;

        /* overrides. */
    public:
            // IUnkown
        virtual hresult __stdcall QueryInterface
            ( const ::IID& model, void ** alias );

            // IITemNameLimits
        virtual hresult __stdcall GetMaxLength
            ( const wchar_t * file, int * length );
        virtual hresult __stdcall GetValidCharacters
            ( wchar_t ** valid, wchar_t ** invalid );

            // IObjectProvider
        virtual hresult __stdcall QueryObject
            ( const ::GUID& object, const ::IID& model, void ** instance );

            // IPersist
        virtual hresult __stdcall GetClassID
            ( ::CLSID * guid );

            // IPersistFolder
        virtual hresult __stdcall Initialize
            ( const ::ITEMIDLIST * path );

            // IPersistFolder2
        virtual hresult __stdcall GetCurFolder
            ( ::ITEMIDLIST ** path );

            // IPersistIDList
        virtual hresult __stdcall GetIDList
            ( ::ITEMIDLIST ** path );
        virtual hresult __stdcall SetIDList
            ( const ::ITEMIDLIST * path );

            // IShellFolder
        virtual hresult __stdcall BindToObject (
            const ::ITEMIDLIST * path, ::IBindCtx * context,
            const ::IID& model, void ** instance );
        virtual hresult __stdcall BindToStorage (
            const ::ITEMIDLIST * path, ::IBindCtx * context,
            const ::IID& model, void ** instance );
        virtual hresult __stdcall CompareIDs (
            lparam param, const ::ITEMIDLIST * lhs, const ::ITEMIDLIST * rhs );
        virtual hresult __stdcall CreateViewObject
            ( hwnd owner, const ::IID& model, void ** instance );
        virtual hresult __stdcall EnumObjects
            ( hwnd owner, ::SHCONTF flags, ::IEnumIDList ** list );
        virtual hresult __stdcall GetAttributesOf
            ( uint count, const ::ITEMIDLIST ** paths, ::SFGAOF * mask );
        virtual hresult __stdcall GetDisplayNameOf
            ( const ::ITEMIDLIST * path, ::SHGDNF flags, ::STRRET * name );
        virtual hresult __stdcall GetUIObjectOf (
            hwnd owner, uint count, const ::ITEMIDLIST ** paths,
            const ::IID& model, uint *, void ** instance );
        virtual hresult __stdcall ParseDisplayName (
            hwnd owner, ::IBindCtx * context, wchar_t * name,
            ulong * eaten, ::ITEMIDLIST ** path, ulong * attributes );
        virtual hresult __stdcall SetNameOf (
            hwnd owner, const ::ITEMIDLIST * path, const wchar_t * name,
            ::SHGDNF flags, ::ITEMIDLIST ** npath );

            // IShellFolder2
        virtual hresult __stdcall EnumSearches
            ( ::IEnumExtraSearch ** searchs );
        virtual hresult __stdcall GetDefaultColumn
            ( dword resource, ulong * sort, ulong * display );
        virtual hresult __stdcall GetDefaultColumnState
            ( uint column, ::SHCOLSTATEF * flags );
        virtual hresult __stdcall GetDefaultSearchGUID ( ::GUID * search );
        virtual hresult __stdcall GetDetailsEx (
            const ::ITEMIDLIST * path, const ::SHCOLUMNID * column,
            ::VARIANT * variant );
        virtual hresult __stdcall GetDetailsOf (
            const ::ITEMIDLIST * path, uint column, ::SHELLDETAILS * details );
        virtual hresult __stdcall MapColumnToSCID
            ( uint column, ::SHCOLUMNID * identifier );

            // IStorage
        virtual hresult __stdcall CreateStream (
            const wchar_t * name, dword mode,
            dword, dword, ::IStream ** stream );
        virtual hresult __stdcall OpenStream (
            const wchar_t * name, void*, dword mode,
            dword, ::IStream ** stream );
        virtual hresult __stdcall CreateStorage (
            const wchar_t * name, dword mode,
            dword, dword, ::IStorage ** storage );
        virtual hresult __stdcall OpenStorage (
            const wchar_t * name, ::IStorage * priority, dword mode,
            ::SNB exclude, dword, ::IStorage ** storage );
        virtual hresult __stdcall CopyTo (
            dword count, const ::IID * excludes,
            ::SNB exclude, ::IStorage * destination );
        virtual hresult __stdcall MoveElementTo (
            const wchar_t * name, ::IStorage * destination,
            const wchar_t * newname, dword flags );
        virtual hresult __stdcall Commit ( dword flags );
        virtual hresult __stdcall Revert ();
        virtual hresult __stdcall EnumElements
            ( dword, void*, dword, ::IEnumSTATSTG ** elements );
        virtual hresult __stdcall DestroyElement ( const wchar_t * name );
        virtual hresult __stdcall RenameElement (
            const wchar_t * name, const wchar_t * newname );
        virtual hresult __stdcall SetElementTimes (
            const wchar_t * name, const ::FILETIME * creation,
            const ::FILETIME * access, const ::FILETIME * modification );
        virtual hresult __stdcall SetClass ( const ::IID& model );
        virtual hresult __stdcall SetStateBits ( dword state, dword mask );
        virtual hresult __stdcall Stat (::STATSTG * stats, dword hints );
    };

} } }

#endif /* _w32_shl_ext_Namespace_hpp__ */
