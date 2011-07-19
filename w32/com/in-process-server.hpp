#ifndef _w32_com_InProcessServer_hpp__
#define _w32_com_InProcessServer_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.com.hpp>

extern "C" {

        /*!
         * @brief Maintains a count of the numbe rof live COM object instances.
         *
         * The COM infrastructure must be able to determine if a DLL, from which
         * objects were allocated, can be unloaded safely. Each time you create
         * an object who'se pointer is returned outside the DLL, increment this
         * count. Conversely, when those objects' lifetimes end, decrement the
         * counter.
         *
         * Failure to adjust the counter has severe consequences:
         *   - omission of increment may result in program crashes;
         *   - omission of decrement may result in memory leaks.
         */
    extern volatile ::LONG GlobalObjectCount;

        /*!
         * @brief Hook for the COM infrastructure: library unloading safety.
         * @return \c S_OK iff \c GlobalObjectCount is 0, \c S_FALSE if not.
         *
         * This method basically tells COM if the \c GlobalObjectCount is 0.
         */
    ::HRESULT __stdcall DllCanUnloadNow ();

        /*!
         * @brief Hook for the COM infrastructure: library initialization.
         */
    ::ULONG __stdcall DllMain (
        ::HINSTANCE instance, ::DWORD reason, ::LPVOID
        );

        /*!
         * @brief Hook for the COM infrastructure: object instantiation.
         */
    ::HRESULT __stdcall DllGetClassObject (
        const ::GUID& class_, const ::GUID& interface_, void ** object
        );

}

#endif /* _w32_com_InProcessServer_hpp__ */
