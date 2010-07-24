// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <boost/python.hpp>
#include <w32.hpp>
#include <w32.rgs.hpp>

BOOST_PYTHON_MODULE(pyw32rgs)
{

    boost::python::class_< w32::rgs::Key >
        ( "Key", boost::python::no_init )
#define ENUM(symbol) \
        .def( #symbol, &w32::rgs::Key::##symbol ) \
            .staticmethod( #symbol )
        ENUM(machine)
        ENUM(user)
        ENUM(users)
        ENUM(classes)
#   if (_WIN32_WINNT >= 0x600)
        ENUM(configuration)
#   endif
#undef ENUM
        .def( boost::python::init<
            const w32::rgs::Key&,const w32::string&>() )
        .def( "flush", &w32::rgs::Key::flush )
        .def( "remove", &w32::rgs::Key::remove )
        .def( "delete", &w32::rgs::Key::delete_ )
        ;

}

namespace w32 {

        // Can't be "declspec(dllexport)"ed.
    std::locale::id Error::Put::id;

}

    // Link automagically.
#pragma comment ( lib, "w32.lib" )
#pragma comment ( lib, "w32.dbg.lib" )
#pragma comment ( lib, "w32.rgs.lib" )
