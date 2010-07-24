.. _w32-astring:

####################################################################
  :cpp:class:`w32::astring` --- ANSI (multi-byte) character string  
####################################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:namespace:: w32

.. cpp:class:: astring

   Encapsulates dynamic (de-)allocation of character strings for encoded text.

   Multi-byte strings are strings encoded in single or double byte
   character encodings. Since the binary data can be encoded in more than
   one way, each string carries information about it's encoding scheme.

   Strictly speaking, some instances of this class may carry data in
   "utf-8" format, which qualifies them as "unicode". Converting to utf-8
   is another reason to use this class: it is an increasingly popular
   encoding, especially on the internet.

   .. note::

      Note that the preferred way to hold string data in the Win32 API is to
      use the "unicode" strings. That may well turn out to less bugs,
      greater compatibility and more efficient. Yes, "ANSI" versions of all
      Win32 functions convert data to unicode at input and output. You
      should only use this class for interoperability with legacy code and
      protocols.

   .. note::

      The implementation attempts no optimization to reduce memory footprint,
      such as copy-on-write semantics. Qualified developpers have expressed
      their concerns [#]_ about the C++ standard strings in various
      implementations. This library is not intended for implementation of whole
      programs, but rather targets ease of use when interfacing with the Win32c
      API. The focus is on authoring correct programs quickly. In program
      segments not interfacing with the Win32c API, the use of ``std::string``
      and ``std::wstring`` is preferred for performance and portability.

   .. cpp:type:: size_type

   .. cpp:function:: astring()

      Creates an empty string.

   .. cpp:function:: astring ( const astring& other )

      Creates a copy of ``other``.

   .. cpp:function:: astring( const char * data )

      Creates a copy of ``data``.

      :param data: Contents to duplicate.

   .. cpp:function:: astring( const char* data, Codepage encoding )

      Creates a copy of ``data``.

      :param data: Contents to duplicate.
      :param encoding: Code page in which ```data`` will be encoded.

   .. cpp:function:: astring ( w32::string data )

      Decodes ``data``.

      :param data: Contents to encode.

   .. cpp:function:: astring ( std::string data, Codepage encoding )

      Decodes ``data``.

      :param data: Contents to encode.
      :param encoding: Character encoding used for the result.

   .. cpp:function:: ~astring ()

      Frees any allocated memory.

   .. cpp:function:: Codepage encoding () const

      Obtains the code page used to encode the character buffer.

   .. cpp:function:: size_type size () const

      Obtains the number of ``char`` items in the character buffer.

      .. warning::

         For code pages that represent multi-byte character encodings, this is
         **not** equal to the number of *characters* in the string!

   .. cpp:function:: size_type length () const

      Alias for :cpp:func:`w32::astring::size`.

   .. cpp:function:: char* data ()

      Obtains read-write access to the character buffer.

   .. cpp:function:: const char* data () const

      Obtains read-only access to the character buffer.

   .. cpp:function:: const char* c_str () const

      Alias for :cpp:func:`w32::astring::data`.

      .. warning::

         In contrast with ``std::string::c_str()``, this method does **not**
         remove null bytes from the character buffer.

   .. cpp:function:: swap( astring& rhs )

       Exchanges contents with ``rhs`` in ``O(1)``.

       :param rhs: Other string to exchange contents with.

.. [#] See the SGI design document discussing `representations of strings
    <http://www.sgi.com/tech/stl/string_discussion.html>`_ in the STL.
