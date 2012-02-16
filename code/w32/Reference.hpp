#ifndef _w32_Reference_hpp__
#define _w32_Reference_hpp__

// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
