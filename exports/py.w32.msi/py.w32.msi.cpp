// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <boost/python.hpp>
#include <w32.hpp>
#include <w32.msi.hpp>

namespace msi = w32::msi;

namespace {

    void translate ( const msi::Error& )
    {
        PyErr_SetString(PyExc_RuntimeError,"Unchecked exception.");
    }

    void translate ( const msi::Database::OpeningFailed& )
    {
        PyErr_SetString(PyExc_ValueError,"Could not open database.");
    }

    void translate ( const msi::Database::InvalidParameter& )
    {
        PyErr_SetString(PyExc_ValueError,"Invalid parameter.");
    }

    void translate ( const msi::View::BadSqlSyntax& )
    {
        PyErr_SetString(PyExc_ValueError,"Bad SQL syntax.");
    }

    void translate ( const msi::View::InvalidParameter& )
    {
        PyErr_SetString(PyExc_ValueError,"Invalid parameter.");
    }

    void translate ( const msi::View::NoMoreRecords& )
    {
        PyErr_SetString(PyExc_StopIteration,"No more records.");
    }

    void translate ( const msi::Record::CreationFailed& )
    {
        PyErr_SetString(PyExc_ValueError,"Creation failed.");
    }

    void translate ( const msi::Record::InvalidHandle& )
    {
        PyErr_SetString(PyExc_ValueError,"Invalid handle.");
    }

    void translate ( const msi::Record::NullInteger& )
    {
        PyErr_SetString(PyExc_ValueError,"Null integer.");
    }

    void translate ( const msi::Record::InvalidParameter& )
    {
        PyErr_SetString(PyExc_ValueError,"Invalid parameter.");
    }

    void translate ( const msi::Record::InvalidField& )
    {
        PyErr_SetString(PyExc_ValueError,"Invalid field.");
    }

}

BOOST_PYTHON_MODULE(pyw32msi)
{
        // Export general library exceptions.
    boost::python::register_exception_translator
        < msi::Error >(
            (void(*)(const msi::Error&))translate
            );

        // Export database class.
    boost::python::class_< msi::Database, boost::noncopyable > database
        ( "Database", boost::python::init<std::wstring,msi::Database::Mode>() );

        // Export database nested types.
    { boost::python::scope scope = database;

            // Export database opening/creation mode class.
        boost::python::class_< msi::Database::Mode > mode
            ( "Mode", boost::python::no_init );

            // Define database opening/creationg mode class data.
        mode
            .def( "ReadOnly", msi::Database::Mode::readonly )
                .staticmethod("ReadOnly")
            .def( "Transaction", msi::Database::Mode::transaction )
                .staticmethod("Transaction")
            .def( "Create", msi::Database::Mode::create )
                .staticmethod("Create")
            .def( "Direct", msi::Database::Mode::direct )
                .staticmethod("Direct")
            .def( "CreateDirect", msi::Database::Mode::createdirect )
                .staticmethod("CreateDirect")
            ;

            // Export database state class.
        boost::python::class_< msi::Database::State > state
            ( "DatabaseState", boost::python::no_init );

            // Define database state class data.
        state
            .def( "Read", msi::Database::State::read )
                .staticmethod("Read")
            .def( "Write", msi::Database::State::write )
                .staticmethod("Write")
            .def( "Error", msi::Database::State::error )
                .staticmethod("Error")
            ;
    }

        // Define database functions.
    database
        .def( "commit", &msi::Database::commit )
        .def( "mode", &msi::Database::mode )
        .def( "state", &msi::Database::state )
        ;

        // Export view class.
    boost::python::class_< msi::View, boost::noncopyable > view
        ( "View", boost::python::init<const msi::Database&,std::wstring>() );

        // Export view exceptions.
    boost::python::register_exception_translator
        < msi::View::NoMoreRecords >(
            (void(*)(const msi::View::NoMoreRecords&))translate
            );
    boost::python::register_exception_translator
        < msi::View::InvalidParameter >(
            (void(*)(const msi::View::InvalidParameter&))translate
            );
    boost::python::register_exception_translator
        < msi::View::BadSqlSyntax >(
            (void(*)(const msi::View::BadSqlSyntax&))translate
            );

        // Export record class.
    boost::python::class_< msi::Record, boost::noncopyable > record
        ( "Record", boost::python::init<msi::View&>() );

        // Export view nested types.
    { boost::python::scope scope = view;

            // Export column class.
        boost::python::class_< msi::View::Column > column
            ( "Column", boost::python::no_init );

            // Define column symbols.
        column
            .def( "Names", msi::View::Column::names )
                .staticmethod("Names")
            .def( "Types", msi::View::Column::types )
                .staticmethod("Types")
            ;

            // Export column information class.
        boost::python::class_<
            msi::Columns,
                boost::python::bases<msi::Record>, boost::noncopyable
            > columns
            ( "Columns",
              boost::python::init<const msi::View&,const msi::View::Column&>()
            );
    }

        // Define view functions.
    view
        .def( "execute", &msi::View::execute )
        .def( "close", &msi::View::close )
        ;

        // Export record exceptions.
    boost::python::register_exception_translator
        < msi::Record::CreationFailed >(
            (void(*)(const msi::Record::CreationFailed&))translate
            );
    boost::python::register_exception_translator
        < msi::Record::InvalidHandle >(
            (void(*)(const msi::Record::InvalidHandle&))translate
            );
    boost::python::register_exception_translator
        < msi::Record::NullInteger >(
            (void(*)(const msi::Record::NullInteger&))translate
            );
    boost::python::register_exception_translator
        < msi::Record::InvalidParameter >(
            (void(*)(const msi::Record::InvalidParameter&))translate
            );
    boost::python::register_exception_translator
        < msi::Record::InvalidField >(
            (void(*)(const msi::Record::InvalidField&))translate
            );

        // Export record nested types.
    { boost::python::scope scope = record;
    }

        // Define record functions.
    record
        .def( "__len__", &msi::Record::fields )
        .def( "sizeof", &msi::Record::size )
        .def( "__getitem__", &msi::Record::string )
        ;

}

namespace w32 {

        // Can't be "declspec(dllexport)"ed.
    std::locale::id Error::Put::id;

}

    // Link automagically.
#pragma comment ( lib, "w32.lib" )
#pragma comment ( lib, "w32.dbg.lib" )
#pragma comment ( lib, "w32.msi.lib" )
