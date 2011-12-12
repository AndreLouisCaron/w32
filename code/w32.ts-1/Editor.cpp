// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.ts-1/Editor.hpp>
#include <w32.ts-1/Task.hpp>

namespace w32 { namespace ts {

    Editor::Editor ( Task& task )
        : myTask(task)
    {
    }

    void Editor::application ( const string& value )
    {
        const com::Result result =
            myTask.ptr()->SetApplicationName(value.c_str());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITask, SetApplicationName, result);
        }
    }

    void Editor::arguments ( const string& value )
    {
        const com::Result result =
            myTask.ptr()->SetParameters(value.c_str());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITask, SetParameters, result);
        }
    }

    void Editor::creator ( const string& value )
    {
        const com::Result result = myTask.ptr()->SetCreator(value.c_str());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITask,SetCreator,result);
        }
    }

    void Editor::account ( const string& value )
    {
        const com::Result result =
            myTask.ptr()->SetAccountInformation(value.c_str(),0);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITask,SetAccountInformation,result);
        }
    }

    void Editor::account ( const string& value, const string& password )
    {
        const com::Result result =
            myTask.ptr()->SetAccountInformation(value.data(), password.data());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITask,SetAccountInformation,result);
        }
    }

    void Editor::commit ()
    {
        com::cast< ::IPersistFile >(myTask.ptr())->Save(0, TRUE);
    }

} }
