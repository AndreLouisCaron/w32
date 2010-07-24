// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/Error.hpp>
#include <w32/string.hpp>
#include <cstdio>
#include <cstring>
#include <sstream>

namespace w32 {

    Error::Error ( Code code ) throw ()
        : myCode(code)
    {
        std::cerr << "Error: " << code << "." << std::endl;
    }

    Error::Code Error::code () const throw ()
    {
        return (myCode);
    }

    string Error::what () const
    {
        std::wostringstream message;
        message << (*this);
        return (message.str());
    }

}
