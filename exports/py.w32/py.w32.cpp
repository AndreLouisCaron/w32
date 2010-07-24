// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <boost/python.hpp>
#include <w32.hpp>

namespace {

    void translator ( const w32::Error& error )
    {
        std::ostringstream message;
        message << "[[[ " << error << " ]]]";
        PyErr_SetString(PyExc_RuntimeError, message.str().c_str());
    }

}

BOOST_PYTHON_MODULE(pyw32)
{

    boost::python::register_exception_translator
        < w32::Error >(translator);

    boost::python::class_< w32::Architecture >
        ( "Architecture", boost::python::no_init )
        .def( "x86", &w32::Architecture::x86 )
            .staticmethod("x86")
        .def( "x64", &w32::Architecture::x64 )
            .staticmethod("x64")
        .def( "ia64", &w32::Architecture::ia64 )
            .staticmethod("ia64")
        .def( "unknown", &w32::Architecture::unknown )
            .staticmethod("unknown")
        .def( "__eq__", &w32::Architecture::operator == )
        .def( "__ne__", &w32::Architecture::operator != )
        ;

    boost::python::class_< w32::Codepage >
        ( "Codepage", boost::python::no_init )
        .def( "ansi", &w32::Codepage::ansi )
            .staticmethod("ansi")
        .def( "oem", &w32::Codepage::oem )
            .staticmethod("oem")
        .def( "utf7", &w32::Codepage::utf7 )
            .staticmethod("utf7")
        .def( "utf8", &w32::Codepage::utf8 )
            .staticmethod("utf8")
        .def( "valid", &w32::Codepage::valid )
        .def( "__eq__", &w32::Codepage::operator == )
        .def( "__ne__", &w32::Codepage::operator != )
        ;

    boost::python::class_< w32::Environment >
        ( "Environment" )
        .def( "empty", &w32::Environment::empty )
            .staticmethod( "empty" )
        .def( "get", &w32::Environment::get )
            .staticmethod( "get" )
        .def( "__getitem__", &w32::Environment::operator[] )
        ;

    boost::python::class_< w32::Module >
        ( "Module" )
        .def( "load", &w32::Module::load )
            .staticmethod("load")
        .def( "name", &w32::Module::name )
        .def( "path", &w32::Module::path )
        //.def( "get", &w32::Module::get )
        //    -> void* not supported by boost :-(
        ;

    boost::python::class_< w32::Resource >
        ( "Resource", boost::python::init<const w32::Module&,int>() )
        .def( boost::python::init<const w32::Module&,const w32::string&>() )
        .def( boost::python::init<const w32::Module&,const std::string&>() )
        .def( boost::python::init<const w32::Module&,const std::wstring&>() )
        .def( "module", &w32::Resource::module,
            boost::python::return_internal_reference<>() )
        ;

    boost::python::class_< w32::string >
        ( "string" )
        .def( boost::python::init<const std::wstring&>() )
        .def( "__len__", &w32::string::length )
        .def( "__unicode__", &w32::string::operator const std::wstring )
        .def( "__repr__", &w32::string::operator const std::wstring )
        .def( "__add__", &w32::string::operator+ )
        .def( "__iadd__", &w32::string::operator+=,
            boost::python::return_internal_reference<>() )
        //.def( "__getitem__", &w32::string::operator[] )
        //.def( "__add__", &w32::string::operator+ )
        .def( "swap", &w32::string::swap )
        ;

    boost::python::class_< w32::astring >
        ( "astring" )
        .def( boost::python::init<const std::string&>() )
        .def( "__len__", &w32::astring::length )
        .def( "__str__", &w32::astring::operator const std::string )
        .def( "__repr__", &w32::astring::operator const std::string )
        //.def( "__getitem__", &w32::astring::operator[] )
        //.def( "__add__", &w32::astring::operator+ )
        .def( "encoding", &w32::astring::encoding )
        .def( "swap", &w32::astring::swap )
        ;

    boost::python::class_< w32::bstring >
        ( "bstring" )
        .def( boost::python::init<const std::wstring&>() )
        .def( "__repr__", &w32::string::operator const std::wstring )
        ;

    boost::python::class_< w32::mstring >
        ( "mstring", boost::python::no_init )
        ;

    boost::python::class_< w32::strings >
        ( "strings" )
        .def( "__len__", &w32::strings::size )
        //.def( "__getitem__", &w32::strings::operator[] )
        ;

    boost::python::class_< w32::System >
        ( "System" )
        .def( "architecture", &w32::System::architecture )
        .def( "pagesize", &w32::System::pagesize )
        .def( "processors", &w32::System::processors )
        ;

    boost::python::class_< w32::Time >
        ( "Time" )
        .def( "year", &w32::Time::year )
        .def( "month", &w32::Time::month )
        .def( "day", &w32::Time::day )
        .def ( "hour", &w32::Time::hour )
        .def ( "minute", &w32::Time::minute )
        .def ( "second", &w32::Time::second )
        .def ( "millisecond", &w32::Time::millisecond )
        ;

    boost::python::class_< w32::Timespan >
        ( "Timespan" )
        .def( "ticks", &w32::Timespan::ticks )
        ;

    boost::python::class_< w32::Variant, boost::noncopyable >
        ( "Variant", boost::python::no_init )
        .def( "clear", &w32::Variant::clear )
        ;

    boost::python::class_< w32::Version >
        ( "Version" )
        .def( "major", &w32::Version::major )
        .def( "minor", &w32::Version::minor )
        .def( "build", &w32::Version::build )
        .def( "__eq__", &w32::Version::operator == )
        .def( "__lt__", &w32::Version::operator < )
        ;

    boost::python::class_< w32::Variant >
        variant ( "Variant" );
    { boost::python::scope _(variant);
        boost::python::class_< w32::Variant::Type >
            ( "Type", boost::python::no_init )
            .def( "empty", &w32::Variant::Type::empty )
                .staticmethod( "empty" )
            .def( "null", &w32::Variant::Type::null )
                .staticmethod( "null" )
            .def( "boolean", &w32::Variant::Type::boolean )
                .staticmethod( "boolean" )
            .def( "integer", &w32::Variant::Type::integer )
                .staticmethod( "integer" )
            .def( "result", &w32::Variant::Type::result )
                .staticmethod( "result" )
            .def( "string", &w32::Variant::Type::string )
                .staticmethod( "string" )
            /*.def( "astring", &w32::Variant::Type::astring )
                .staticmethod( "astring" )
            .def( "bstring", &w32::Variant::Type::bstring )
                .staticmethod( "bstring" )*/
            .def( "__eq__", &w32::Variant::Type::operator == )
            .def( "__ne__", &w32::Variant::Type::operator != )
            .def( "__hash__", &w32::Variant::Type::value )
            //.def( "__lt__", &w32::Variant::operator < )
            ;
    }
    variant
        .def( boost::python::init<const w32::Variant&,const w32::Variant::Type&>() )
        .def( "clear", &w32::Variant::clear )
        .def( "coerce", &w32::Variant::coerce )
        .def( "type", &w32::Variant::type )
        .def( "bstring", &w32::Variant::operator w32::bstring )
        ;

}

namespace w32 {

        // Can't be "declspec(dllexport)"ed.
    std::locale::id Error::Put::id;

}

    // Link automagically.
#pragma comment ( lib, "w32.lib" )
#pragma comment ( lib, "w32.dbg.lib" )
