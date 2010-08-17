#ifndef _w32_xml_dom_Document_hpp__
#define _w32_xml_dom_Document_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace xml { namespace dom {

    class Attributes;
    class Element;
    class Error;
    class List;
    class Node;

        /*!
         * @brief XML document.
         */
    class W32_XML_DOM_EXPORT Document
    {
        /* nested types. */
    public:
        typedef com::Ptr< ::IXMLDOMDocument2 > Ptr;

        /* data. */
    private:
        Ptr myPtr;

        /* construction. */
    public:
        Document ();
        Document ( const Ptr& ptr );

        /* methods. */
    public:
        Ptr get () const;
        void validateOnParse ( bool enable );
        void preserveWhiteSpace ( bool enable );
        void property_ ( const string& name, bool enable );
        void prohibitDTD ( bool enable );
        void resolveExternals ( bool enable );

        bool open ( const string& url );
        bool load ( const string& content );
        Error validate () const;

            /*!
             * @brief Creates an element node.
             */
        Element element ( const string& tag );

             /*!
              * @brief XPath query expecting a single result.
              */
        Node match ( const string& query ) const;

             /*!
              * @brief XPath query expecting multiple results.
              */
        List matches ( const string& query ) const;
    };

} } }

template<> inline w32::com::Guid
    w32::com::guidof< ::IXMLDOMDocument2 > ()
{
    return (IID_IXMLDOMDocument2);
}

#endif /* _w32_xml_dom_Document_hpp__ */
