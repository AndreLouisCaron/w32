#ifndef _w32_com_Wrapper_hpp__
#define _w32_com_Wrapper_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32.com/Ptr.hpp>

namespace w32{ namespace com {

        /*!
         * @brief Holds a COM handle and defines common methods.
         */
    template<typename T>
    class Wrapper
    {
        /* nested types. */
    public:
        typedef T Binding;
        typedef com::Ptr<Binding> Ptr;

        /* nested types. */
    protected:
        typedef Wrapper<T> Base;

    public:
            /*!
             * @brief Adapts a wrapper class to a new interface.
             *
             * Creates a wrapper object which wraps the same COM object, but
             * with a different (typically extended) interface. This class
             * automagically benefits from an existing wrapper class.
             */
        template<typename U>
        class Rebind
            : public Wrapper<U>
        {
            /* construction. */
        public:
                /*!
                 * @brief Extracts a pointer to the interface.
                 */
            Rebind ( ::IUnknown * object )
                : Wrapper<U>(cast<typename Wrapper::Binding>(object))
            {}

                /*!
                 * @brief Extracts a pointer to the interface.
                 */
            template<typename V>
            Rebind ( const com::Ptr<V>& object )
                : Wrapper<U>(cast<typename Wrapper<U>::Binding>(object))
            {}

                /*!
                 * @brief Extracts a pointer to the interface.
                 */
            template<typename V>
            Rebind ( Wrapper<V>& object )
                : Wrapper<U>(cast<typename Wrapper<U>::Binding>(object.ptr()))
            {}
        };

        /* data. */
    private:
        Ptr myBinding;

        /* construction. */
    public:
            /*!
             * @brief Acquire owneship of handle, no AddRef().
             */
        explicit Wrapper ( Binding * object = 0 )
            : myBinding(object)
        {}

        explicit Wrapper ( const Ptr& object )
            : myBinding(object)
        {}

        /* methods. */
    public:
            /*!
             * @brief Access object, not null-safe.
             */
        Binding& backend () const {
            return (*myBinding);
        }

            /*!
             * @brief Read-only access to the handle.
             */
        const Ptr& ptr () const {
            return (myBinding);
        }
    };

} }

#endif /* _w32_com_Wrapper_hpp__ */
