#ifndef _w32_dbg_StructuredException_hpp__
#define _w32_dbg_StructuredException_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>

namespace w32 { namespace dbg {

    class StructuredException
    {
        /* nested types. */
    public:
        typedef ::_se_translator_function Filter;

        class FilterReplacement;

        /* class data. */
    public:
        static const Filter translator ();

        /* construction. */
    public:
        virtual ~StructuredException () {
        }

        /* methods. */
    public:
        virtual const char * what () const = 0;
    };

    class StructuredException::FilterReplacement :
        private NotCopyable
    {
        /* data. */
    private:
        Filter myPredecessor;

        /* construction. */
    public:
        explicit FilterReplacement ( Filter filter = translator() );
        ~FilterReplacement ();
    };

    class UnexpectedException :
        public StructuredException
    {
        /* overrides. */
    public:
        virtual const char * what () const {
            return ("Undocumented structured exception.");
        }
    };

    class AccessViolation :
        public StructuredException
    {
        /* overrides. */
    public:
        virtual const char * what () const {
            return ("Access violation.");
        }
    };

    class DivisionByZero :
        public StructuredException
    {
        /* overrides. */
    public:
        virtual const char * what () const {
            return ("Division by zero.");
        }
    };

} }

#endif /* _w32_dbg_StructuredException_hpp__ */
