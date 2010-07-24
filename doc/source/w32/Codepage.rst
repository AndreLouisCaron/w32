.. _w32-codepage:

#####################################################
  :cpp:class:`w32::Codepage` --- Character encoding  
#####################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:namespace:: w32

.. cpp:class:: w32::Codepage

   A character encoding is a mapping of numeric identifiers to specific
   characters. Many such mappings exist.

   .. note::

      Although the Unicode Transformation Formats are technically character
      encodings, text data in UTF-16 is not usually considered *encoded*.
      This is due to the fact that it is the most complete character
      representation and can be *encoded* into any other encoding, albeit
      lossyly in most cases.

   .. cpp:type:: Value

      Defines the enumerated values' type.

   .. cpp:function:: static const Codepage ansi()

      ANSI/ASCII codepage.

   .. cpp:function:: static const Codepage oem()

      OEM codepage.

   .. cpp:function:: static const Codepage utf7()

      UTF-7 codepage.

   .. cpp:function:: static const Codepage utf8()

      UTF-8 codepage.

   .. cpp:function:: bool valid() const

      Verifies that the code page number is valid.

   .. cpp:function:: Value value () const

       Returns the native representation for the enumeration.

       .. seealso::

          :cpp:func:`w32::Architecture::operator Value`

   .. cpp:function:: operator Value () const

       Returns the native representation for the enumeration.

       .. seealso::

          :cpp:func:`w32::Architecture::value`
