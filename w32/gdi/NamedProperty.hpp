#ifndef _win32c_gdi_NamedProperty_hpp__
#define _win32c_gdi_NamedProperty_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <win32c/gdi/Property.hpp>

namespace win32c { namespace gdi {

    class NamedProperty :
        public Property
    {
        /* data. */
    private:
        const std::string myName;

        /* construction. */
    public:
        NamedProperty ( Window& owner, const std::string& name )
            : Property(owner), myName(name)
        {}

        /* overrides. */
    public:
        const char * name () const {
            return (myName.c_str());
        }
    };

} }

#endif /* _win32c_gdi_NamedProperty_hpp__ */
