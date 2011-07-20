// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/io/OutputFile.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE open ( ::LPCWSTR path, ::DWORD sharing, ::DWORD mode )
    {
        const ::HANDLE result = ::CreateFileW(
            path, GENERIC_WRITE, sharing, 0, mode, 0, 0
            );
        if ( result == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateFile,error);
        }
        return (result);
    }

}

namespace w32 { namespace io {

    const OutputFile::Mode OutputFile::Mode::open ()
    {
        return (OPEN_EXISTING);
    }

    const OutputFile::Mode OutputFile::Mode::create ()
    {
        return (CREATE_NEW);
    }

    const OutputFile::Mode OutputFile::Mode::replace ()
    {
        return (TRUNCATE_EXISTING);
    }

    const OutputFile::Mode OutputFile::Mode::squash ()
    {
        return (CREATE_ALWAYS);
    }

    const OutputFile::Mode OutputFile::Mode::append ()
    {
        return (OPEN_ALWAYS);
    }

    OutputFile::Mode::Mode ( Value value )
        : myValue(value)
    {
    }

    OutputFile::Mode::Value OutputFile::Mode::value () const
    {
        return (myValue);
    }

    OutputFile::OutputFile ( const string& path, const Mode& mode )
        : Stream(Object::claim(
              ::open(path.c_str(), 0, mode.value())
              ))
    {
    }

} }
