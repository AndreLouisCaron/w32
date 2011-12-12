// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.dbg/StructuredException.hpp>

namespace {

        // Maps exception codes to typed exception objects.
    void TranslationProcedure (
        unsigned int exception, ::_EXCEPTION_POINTERS * pointers
    )
    {
        if ( exception == EXCEPTION_INT_DIVIDE_BY_ZERO ) {
            throw (w32::dbg::DivisionByZero());
        }
        else if ( exception == EXCEPTION_ACCESS_VIOLATION ) {
            throw (w32::dbg::AccessViolation());
        }
        throw (w32::dbg::UnexpectedException());
    }

}

namespace w32 { namespace dbg {

    StructuredException::FilterReplacement::FilterReplacement ( Filter filter )
        : myPredecessor(::_set_se_translator(filter))
    {
    }

    StructuredException::FilterReplacement::~FilterReplacement ()
    {
        ::_set_se_translator(myPredecessor);
    }

    const StructuredException::Filter StructuredException::translator ()
    {
        return (&::TranslationProcedure);
    }

} }
