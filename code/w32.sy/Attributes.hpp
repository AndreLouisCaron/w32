#ifndef _w32_sy_Attributes_hpp__
#define _w32_sy_Attributes_hpp__

/*!
 * @file w32.sy/Attributes.hpp
 * @author Andre Caron
 */

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>

namespace w32 { namespace sy {

        /*!
         * @brief Contains a sy descriptor and indicates if it is
         *    inheritable (by who, a child process?).
         */
    class Attributes :
        private NotCopyable
    {
        /* nested types. */
    public:
        typedef ::SECURITY_ATTRIBUTES Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    private:
            // Not sure how to use this yet...
        Attributes ();

    public:

        /* methods. */
    public:
        Data& get ();
        const Data& get () const;

        bool inheritable () const;
        void inheritable ( bool value );
    };

} }

#endif /* _w32_sy_Attributes_hpp__ */
