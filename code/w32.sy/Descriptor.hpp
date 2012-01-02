#ifndef _w32_sy_Descriptor_hpp__
#define _w32_sy_Descriptor_hpp__

/*!
 * @file w32.sy/Descriptor.hpp
 * @author Andre Caron
 */

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/types.hpp>
#include <w32.sy/Token.hpp>

namespace w32 { namespace sy {

        /*!
         * @brief Low-level security descriptor.
         *
         * Expresses the level of access to operating system services such as
         * the filesystem, the network and process management.
         */
    class Descriptor :
        private NotCopyable
    {
        /* nested types. */
    public:
        typedef ::SECURITY_DESCRIPTOR Data;

        /* data. */
    private:
        ::SECURITY_DESCRIPTOR myData;

        /* construction. */
    public:
            /*!
             * @brief Creates an empty, but valid, security descriptor.
             */
        Descriptor ();

        /* methods. */
    public:
        Data& get ();
        const Data& get () const;

        dword length () const;
        bool valid () const;
    };

} }

#endif /* _w32_sy_Descriptor_hpp__ */
