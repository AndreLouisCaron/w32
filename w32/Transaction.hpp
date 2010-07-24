#ifndef _w32_Transaction_hpp__
#define _w32_Transaction_hpp__

#include "__configure__.hpp"
#include <w32/Object.hpp>
#include <w32/string.hpp>

namespace w32 {

    class Transaction :
        public Object
    {
        /* nested types. */
    public:
            // Wrapper is in com::Guid!
        //typedef ::GUID Identifier;

        /* construction. */
    public:
            // Create a new transaction.
        Transaction ();
        Transaction ( const string& description );

            // Open an existing transaction.
        //Transaction ( const Identifier& identifier );

        /* methods. */
    public:
        void commit ();
        void rollback ();
    };

}

#endif /* _w32_Transaction_hpp__ */
