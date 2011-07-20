#ifndef _w32_NotCopyable_hpp__
#define _w32_NotCopyable_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 {

/*!
 * @brief Derive from this class to prevent copying and assignment.
 */
class NotCopyable
{
    /* construction. */
protected:
    // This class must be derived from.
    NotCopyable ();

private:
    // Prohibited.
    NotCopyable ( const NotCopyable & );

    /* operators. */
private:
    // Prohibited.
    NotCopyable& operator= ( const NotCopyable & );
};

}

#endif /* _w32_NonCopyable_hpp__ */
