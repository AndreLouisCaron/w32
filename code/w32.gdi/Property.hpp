#ifndef _w32_gdi_Property_hpp__
#define _w32_gdi_Property_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32.gdi/Window.hpp>

namespace w32 { namespace gdi {

        /*!
         * @brief Allows setting named (usally custom) window properties.
         */
    class Property :
        private NotCopyable
    {
        /* data. */
    private:
        Window& myOwner;

        /* construction. */
    public:
        Property ( Window& owner )
            : myOwner(owner)
        {}

        /* methods. */
    public:
            /*!
             * @brief Obtains the name of the window property to get/set.
             */
        virtual const char * name () const = 0;

            /*!
             * @brief Sets the named property.
             */
        void set ( void * value )
        {
            const ::BOOL result = ::SetPropA(
                myOwner.handle(), name(), value
                );
            if ( result == FALSE ) {
                UNCHECKED_WIN32C_ERROR(SetProp,::GetLastError());
            }
        }

            /*!
             * @brief Returns the current value for the named property.
             *
             * The null return value can either mean that the value is
             * effectivly 0 or that the property does not exist.
             */
        void * get () const {
            return (::GetPropA(myOwner.handle(), name()));
        }

            /*!
             * @brief Retrives, then removes the property value.
             *
             * The null return value can either mean that the value was
             * effectivly 0 or that the property did not exist.
             */
        void * remove () {
            return (::RemovePropA(myOwner.handle(), name()));
        }
    };

} }

#endif /* _w32_gdi_Property_hpp__ */
