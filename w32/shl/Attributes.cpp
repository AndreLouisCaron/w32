// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/shl/Attributes.hpp>
#include <w32/shl/Item.hpp>
#include <w32/com/Error.hpp>

namespace w32 { namespace shl {

    const Attributes Attributes::copyable ()
    {
        return (SFGAO_CANCOPY);
    }

    const Attributes Attributes::moveable ()
    {
        return (SFGAO_CANMOVE);
    }

    const Attributes Attributes::linkable ()
    {
        return (SFGAO_CANLINK);
    }

    const Attributes Attributes::storable ()
    {
        return (SFGAO_STORAGE);
    }

    const Attributes Attributes::renamable ()
    {
        return (SFGAO_CANRENAME);
    }

    const Attributes Attributes::deletable ()
    {
        return (SFGAO_CANDELETE);
    }

    const Attributes Attributes::haspropsheet ()
    {
        return (SFGAO_HASPROPSHEET);
    }

    const Attributes Attributes::droptarget ()
    {
        return (SFGAO_DROPTARGET);
    }

    const Attributes Attributes::encrypted ()
    {
        return (SFGAO_ENCRYPTED);
    }

    const Attributes Attributes::slow ()
    {
        return (SFGAO_ISSLOW);
    }

    const Attributes Attributes::ghosted ()
    {
        return (SFGAO_GHOSTED);
    }

    const Attributes Attributes::link ()
    {
        return (SFGAO_LINK);
    }

    const Attributes Attributes::shared ()
    {
        return (SFGAO_SHARE);
    }

    const Attributes Attributes::readonly ()
    {
        return (SFGAO_READONLY);
    }

    const Attributes Attributes::hidden ()
    {
        return (SFGAO_HIDDEN);
    }

    const Attributes Attributes::stream ()
    {
        return (SFGAO_STREAM);
    }

    const Attributes Attributes::container ()
    {
        return (SFGAO_STORAGEANCESTOR);
    }

    const Attributes Attributes::removable ()
    {
        return (SFGAO_REMOVABLE);
    }

    const Attributes Attributes::compressed ()
    {
        return (SFGAO_COMPRESSED);
    }

    const Attributes Attributes::browsable ()
    {
        return (SFGAO_BROWSABLE);
    }

    const Attributes Attributes::folder ()
    {
        return (SFGAO_FOLDER);
    }

    const Attributes Attributes::filesystem ()
    {
        return (SFGAO_FILESYSTEM);
    }

    const Attributes Attributes::subfolders ()
    {
        return (SFGAO_HASSUBFOLDER);
    }

    const Attributes Attributes::all ()
    {
        return  (~::DWORD(0));
    }

    const Attributes Attributes::of ( const Item& item, Attributes mask )
    {
        ::SFGAOF attributes = 0;
        const com::Result result = item.ptr()->GetAttributes(mask, &attributes);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellItem, GetAttributes, result);
        }
        return (attributes);
    }

    Attributes::Attributes ( Value value )
        : myValue(value)
    {
    }

    Attributes::Value Attributes::value () const
    {
        return (myValue);
    }

    Attributes::operator Attributes::Value () const
    {
        return (myValue);
    }

    Attributes::operator bool () const
    {
        return (myValue != 0);
    }

    Attributes& Attributes::operator&= ( const Attributes& rhs )
    {
        myValue &= rhs.myValue; return (*this);
    }

    Attributes& Attributes::operator|= ( const Attributes& rhs )
    {
        myValue |= rhs.myValue; return (*this);
    }

    Attributes Attributes::operator& ( const Attributes& rhs ) const
    {
        Attributes result(*this); result &= rhs; return (result);
    }

    Attributes Attributes::operator| ( const Attributes& rhs ) const
    {
        Attributes result(*this); result |= rhs; return (result);
    }

} }
