/*!
 * @file pymsi.cpp
 * @author Andre Louis Caron
 *
 * @brief Exports bindings to Python for Windows installer wrapper objects.
 */

#include <windows/installer/Database.hpp>
#include <windows/installer/ColumnInformation.hpp>
#include <windows/installer/Hash.hpp>
#include <windows/installer/Product.hpp>
#include <windows/installer/Products.hpp>
#include <windows/installer/UncheckedError.hpp>
#include <windows/installer/View.hpp>

#include <boost/python.hpp>

namespace msi = windows::installer;

namespace {

    void translate ( const msi::UncheckedError& )
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

BOOST_PYTHON_MODULE(_msi)
{
        // Export general library exceptions.
    boost::python::register_exception_translator
        < msi::UncheckedError >(
            (void(*)(const msi::UncheckedError&))translate
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
            .def_readonly( "ReadOnly", msi::Database::Mode::readonly )
            .def_readonly( "Transaction", msi::Database::Mode::transaction )
            .def_readonly( "Create", msi::Database::Mode::create )
            .def_readonly( "Direct", msi::Database::Mode::direct )
            .def_readonly( "CreateDirect", msi::Database::Mode::createdirect )
            ;

            // Export database state class.
        boost::python::class_< msi::Database::State > state
            ( "DatabaseState", boost::python::no_init );

            // Define database state class data.
        state
            .def_readonly( "Read", msi::Database::State::read )
            .def_readonly( "Write", msi::Database::State::write )
            .def_readonly( "Error", msi::Database::State::error )
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
            .def_readonly( "Names", msi::View::Column::names )
            .def_readonly( "Types", msi::View::Column::types )
            ;

            // Export column information class.
        boost::python::class_<
            msi::ColumnInformation,
                boost::python::bases<msi::Record>, boost::noncopyable
            > columninformation
            ( "ColumnInformation",
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
        .def( "__getitem__", &msi::Record::wstring )
        ;

}

#include <windows/installer/ColumnInformation.cpp>
#include <windows/installer/Database.cpp>
#include <windows/installer/Handle.cpp>
#include <windows/installer/Hash.cpp>
#include <windows/installer/Record.cpp>
#include <windows/installer/Product.cpp>
#include <windows/installer/Products.cpp>
#include <windows/installer/View.cpp>
#include <win32c/diagnostics/UncheckedError.cpp>
