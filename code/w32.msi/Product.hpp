#ifndef _w32_msi_Product_hpp__
#define _w32_msi_Product_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32.msi/Guid.hpp>
#include <iosfwd>

namespace w32 { namespace msi {

    /*!
     * @ingroup w32-msi
     * @brief
     */
    class Product
    {
        /* nested types. */
    public:
        typedef Guid Code;

        /* data. */
    private:
        Code myCode;

        /* construction. */
    public:
        explicit Product ( const Code& code );

        /* methods. */
    public:
        const Code& code () const;

        /* operators. */
    public:
        string operator() ( const string& identifier ) const;
    };

} }

#endif /* _w32_msi_Product_hpp__ */
