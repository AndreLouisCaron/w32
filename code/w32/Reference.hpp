#ifndef _w32_Reference_hpp__
#define _w32_Reference_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 {

    /*!
     * @brief Shared ownership of a resource.
     *
     * @note This is implemented with link-reference smart pointers.
     * @warning This class is @e not thread safe.
     */
    template<typename Resource, typename Cleanup=void(*)(Resource)>
    class Reference
    {
        /* nested types. */
    private:
        typedef Reference< Resource, Cleanup > self_type;
        typedef const self_type * link_type;

        /* class methods. */
    private:
        static void abandon ( Resource ) {}

        /* data. */
    private:
        Resource myResource;
        Cleanup myCleanup;
        mutable link_type myHead;
        mutable link_type myTail;

        /* construction. */
    public:
        Reference ()
            : myResource(), myCleanup(&Reference::abandon)
        {
            myHead = myTail = this;
        }

        Reference ( Resource resource )
            : myResource(resource), myCleanup()
        {
            myHead = myTail = this;
        }

        Reference ( Resource resource, Cleanup cleanup )
            : myResource(resource), myCleanup(cleanup)
        {
            myHead = myTail = this;
        }

        Reference ( const Reference& rhs )
            : myResource(rhs.myResource),
              myCleanup(rhs.myCleanup)
        {
            myHead = myTail = this;
            insert(rhs);
        }

        ~Reference ()
        {
            if ( remove() ) {
                myCleanup(myResource);
            }
        }

        /* methods. */
    private:
        void insert ( const self_type& other ) const
        {
            this->myTail = other.myTail;
            other.myTail->myHead = this;
            this->myHead = &other;
            other.myTail = this;
        }

        bool remove () const
        {
            bool unique = this->unique();
            if ( !unique ) {
                this->myTail->myHead = this->myHead;
                this->myHead->myTail = this->myTail;
                myHead = myTail = this;
            }
            return (unique);
        }

    public:
        bool unique () const {
            return ((myHead == this) && (myTail == this));
        }

        Cleanup cleanup () const {
            return (myCleanup);
        }

        /* operators. */
    public:
        Reference& operator= ( const self_type& other )
        {
            if ( remove() ) {
                myCleanup(myResource);
            }
            myResource = other.myResource;
            myCleanup = other.myCleanup;
            insert(other);
            return (*this);
        }

        operator Resource() const
        {
            return (myResource);
        }

        Resource operator-> () const
        {
            return (myResource);
        }
    };

}

#endif /* _w32_Reference_hpp__ */
