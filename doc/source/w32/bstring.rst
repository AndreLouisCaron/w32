.. _w32-bstring:

##########################################################
  :cpp:class:`w32::bstring` --- Binary (or Basic) string  
##########################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:namespace:: w32

.. cpp:class:: w32::bstring

   Encapsulates dynamic (de-)allocation of character strings for interaction
   with Visual Basic libraries.

   .. note::

      Similarity to ``std::wstring`` is intentional. However, note that the
      strings in the standard library provide many methods with equivalents in
      the ``<algorithm>`` header. As this class is designed for ease-of-use of
      OLE and COM APIs rather than massive use, a minimal interface, with
      appropriate conversions to ``std::wstring`` was preferred.

   .. note::

      The implementation attempts no optimization to reduce memory footprint,
      such as copy-on-write semantics. Qualified developpers have expressed
      their concerns [#]_ about the C++ standard strings in various
      implementations. This library is not intended for implementation of whole
      programs, but rather targets ease of use when interfacing with the Win32c
      API. The focus is on authoring correct programs quickly. In program
      segments not interfacing with the Win32c API, the use of ``std::string``
      and ``std::wstring`` is preferred for performance and portability.

   .. cpp:type:: value_type

      Represents the native backend (i.e. ``::BSTR``).

   .. cpp:type:: size_type

      Represents a size.

   .. cpp:type:: char_type

      Represents the character type, as stored in the character buffer.

   .. cpp:type:: const_pointer

      ``const char_type*``

   .. cpp:type:: const_iterator

      RandomAccessIterator_ for the character buffer.

   .. cpp:function:: bstring ()

      Builds an empty string.

   .. cpp:function:: bstring ( value_type contents )

      Creates a copy of ``contents``.

   .. cpp:function:: bstring ( const_pointer contents )
   .. cpp:function:: bstring ( const string& contents )
   .. cpp:function:: bstring ( const bstring& contents )
   .. cpp:function:: explicit bstring ( const box& contents )

   .. cpp:function:: ~bstring ()

      Frees all internally allocated memory.

   .. cpp:function:: value_type value () const

      Obtains the native representation (``BSTR``).

      Although :meth:`data` returns the same thing, this is the preferred
      method for retrieving the native representation of the string
      for interaction with the OLE api (all functions take a non-const
      pointer to the first character).

   .. cpp:function:: const_pointer data () const

      Obtains a pointer to the first character in the string.

      Although :meth:`get` returns the same thing, this is the preferred
      method for retrieving a pointer to the first character in the
      string (especially for const-correctness).

   .. cpp:function:: void swap ( bstring& rhs )

      Exchanges the contents of ``this`` and ``rhs`` in ``O(1)``.

   .. cpp:function:: bool empty () const

      Indicates if ``size() == 0``.

   .. cpp:function:: size_type size () const

      Obtains the number of ``char_type`` items in the buffer. Note that this
      *may not* be the number of *characters*.

   .. cpp:function:: size_type length () const

      Alias for :meth:`size`.

   .. cpp:function:: const_iterator begin () const

      Obtains a RandomAccessIterator_ to the beginning of the sequence.

   .. cpp:function:: const_iterator end () const

      Obtains a RandomAccessIterator_ to the beginning of the sequence.

   .. cpp:function:: bstring& operator= ( const bstring& other )
   .. cpp:function:: bstring& operator= ( const_pointer contents )
   .. cpp:function:: bstring& operator= ( const string& contents )
   .. cpp:function:: bstring& operator= ( const std::wstring& contents )
   .. cpp:function:: operator string() const

      Converts the :class:`w32.bstring` to a standard Windows
      :class:`w32.string`.

   .. cpp:function:: operator std::wstring() const

      Converts the :class:`w32.bstring` to the proper standard string type.


.. cpp:function:: void w32::swap ( bstring& lhs, bstring& rhs )


.. cpp:class:: w32::bstring::box

   Helps perform an optimization by inserting a pre-allocated buffer.

   .. cpp:function:: box ( value_type contents )

      Holds ``contents`` for acquisition by a :class:`w32.bstring`.

   .. cpp:function:: value_type value () const

      Obtains the value provided at construction.

   Performs ``lhs.swap(rhs)``. Overload provided for argument-dependant lookup.


.. [#] See the SGI design document discussing `representations of strings
    <http://www.sgi.com/tech/stl/string_discussion.html>`_ in the STL.

.. _RandomAccessIterator: http://www.sgi.com/tech/stl/RandomAccessIterator.html
