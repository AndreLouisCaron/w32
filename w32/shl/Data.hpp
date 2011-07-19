#ifndef _w32_shl_Data_hpp__
#define _w32_shl_Data_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace shl {

    class Data :
        public com::Wrapper< ::IDataObject >
    {
        /* construction. */
    public:
        explicit Data ( const Ptr& object );

        /* methods. */
    public:
        void get ( ::FORMATETC& format, ::STGMEDIUM& medium ) const;
    };

} }

template<> inline w32::com::Guid
    w32::com::guidof<::IDataObject> ()
{
    return (IID_IDataObject);
}

#endif /* _w32_shl_Data_hpp__ */
