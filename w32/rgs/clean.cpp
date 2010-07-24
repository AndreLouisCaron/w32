// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/rgs/clean.hpp>
#include <w32/rgs/Keys.hpp>
#include <w32/rgs/Values.hpp>

namespace w32 { namespace rgs {

    void clean ( w32::rgs::Key& root )
    {
        for ( w32::rgs::Keys keys(root); keys.next(); ) {
            root.delete_(keys.result());
        }
        for ( w32::rgs::Values values(root); values.next(); ) {
            root.remove(values.result());
        }
    }

    void clean ( Key& root, const string& path )
    {
            // Recursively cleanup first, then remove the key.
        try {
            clean(Key(root,path));
            root.delete_(path);
        }
            // Values can't recursively cleanup.
        catch ( ... ) {
            root.remove(path);
            return;
        }
    }

} }
