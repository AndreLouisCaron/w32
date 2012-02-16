#ifndef _w32_xml_dom_Attributes_hpp__
#define _w32_xml_dom_Attributes_hpp__

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
#include <cstddef>

namespace w32 { namespace xml { namespace dom {

    class Node;

    class Attributes
    {
        /* nested types. */
    public:
        typedef com::Ptr< ::IXMLDOMNamedNodeMap > Ptr;

        typedef long size_type;

        /* data. */
    private:
        Ptr myPtr;

        /* construction. */
    public:
        Attributes ( const Ptr& ptr );

        /* methods. */
    public:
        Ptr get () const;
        size_type length () const;
        size_type size () const;
        void reset ();

        /* operators. */
    public:
        Node operator() ( size_type i ) const;
        Node operator() ( const string& name ) const;
        void operator() ( Node node );
    };

} } }

template<> inline w32::com::Guid
    w32::com::guidof< ::IXMLDOMNamedNodeMap > ()
{
    return (IID_IXMLDOMNamedNodeMap);
}

#endif /* _w32_xml_dom_Attributes_hpp__ */
