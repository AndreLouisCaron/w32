// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/shl/Data.hpp>

namespace w32 { namespace shl {

    Data::Data ( const Ptr& object )
        : com::Wrapper< ::IDataObject >(object)
    {
    }

    void Data::get ( ::FORMATETC& format, ::STGMEDIUM& medium ) const
    {
        const com::Result result(backend().GetData(&format,&medium));
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IDataObject,GetData,result);
        }
    }

} }
