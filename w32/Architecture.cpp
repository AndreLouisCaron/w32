// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/Architecture.hpp>
#include <w32/System.hpp>

namespace w32 {

    const Architecture Architecture::x64 ()
    {
        return (PROCESSOR_ARCHITECTURE_AMD64);
    }

    const Architecture Architecture::ia64 ()
    {
        return (PROCESSOR_ARCHITECTURE_IA64);
    }

    const Architecture Architecture::x86 ()
    {
        return (PROCESSOR_ARCHITECTURE_INTEL);
    }

    const Architecture Architecture::unknown ()
    {
        return (PROCESSOR_ARCHITECTURE_UNKNOWN);
    }

    Architecture::Architecture ( Value value )
        : myValue(value)
    {
    }

    Architecture Architecture::of ( const System& system )
    {
        return (Architecture(system.data().wProcessorArchitecture));
    }

    Architecture::Value Architecture::value () const
    {
        return (myValue);
    }

    Architecture::operator Value() const
    {
        return (value());
    }

    bool Architecture::operator== ( const Architecture& other ) const
    {
        return (myValue == other.myValue);
    }

    bool Architecture::operator!= ( const Architecture& other ) const
    {
        return (myValue != other.myValue);
    }

}
