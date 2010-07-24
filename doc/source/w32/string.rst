.. _w32-string:

########################################################
  :cpp:class:`w32::string` --- Unicode charater string  
########################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:namespace w32

.. cpp:class:: string

   Encapsulates dynamic (de-)allocation of character strings for Unicode text.

   .. note::

      The implementation attempts no optimization to reduce memory footprint,
      such as copy-on-write semantics. Qualified developpers have expressed
      their concerns [#]_ about the C++ standard strings in various
      implementations. This library is not intended for implementation of whole
      programs, but rather targets ease of use when interfacing with the Win32c
      API. The focus is on authoring correct programs quickly. In program
      segments not interfacing with the Win32c API, the use of ``std::string``
      and ``std::wstring`` is preferred for performance and portability.

   .. warning::

      Although they are Unicode strings, there is no proper definition of a
      ``Unicode character``, so don't expect moving up one ``wchar_t`` in the
      string buffer to move you to the next *logical character*.

   .. cpp:type:: size_type

      Unsigned integer type used for representing string length.

   .. cpp:type:: char_type

      ``wchar_t``

   .. cpp:type:: pointer

      ``char_type*``

   .. cpp:type:: const_pointer

      ``const char_type*``

   .. cpp:type:: iterator

      RandomAccessIterator_ for read-write to the string's buffer.

   .. cpp:type:: const_iterator

      RandomAccessIterator_ for read-only to the string's buffer.

   .. cpp:function:: string ()

      Builds a string buffer containing no characters.

   .. cpp:function:: string ( const char * data )

      Decodes a null-terminated string.

      :param data: Character buffer.

      :cpp:func:`w32::Codepage::ansi()` is used as default encoding.

   .. cpp:function:: string ( const char * data, size_type size )

      Decodes a string of known length.

      :param data: Character buffer.
      :param size: Length of ``data``, in bytes.

      :cpp:func:`w32::Codepage::ansi()` is used as default encoding.

   .. cpp:function:: string ( const char * data, Codepage encoding )

      Decodes a null-terminated string.

      :param data: Character buffer.
      :param encoding: Encoding of characters in ``data``.

   .. cpp:function:: string ( const char * data, size_type size, Codepage encoding )

      Decodes a string of known length.

      :param data: Character buffer.
      :param size: Length of ``data``, in bytes.
      :param encoding: Encoding of characters in ``data``.

   .. cpp:function:: string ( const astring& data )

      Decodes a string of known encoding.

      :param data: Contents to decode.
      :param encoding: Encoding of characters in ``data``. Defaults to ``Codepage::ansi()``.

   .. cpp:function:: string ( const std::string& other )

      Decodes a string.

      :param data: Contents to decode.

      :cpp:func:`w32::Codepage::ansi()` is used as default encoding.

   .. cpp:function:: string ( const std::string& other, Codepage encoding )

      Decodes a string.

      :param data: Contents to decode.
      :param encoding: Encoding of characters in ``data``.

   .. cpp:function:: string ( const_pointer data )

      Duplicates a null-terminated Unicode string buffer.

      :param data: Contents to duplicate.

   .. cpp:function:: string ( const wchar_t * data, size_type size )

      Duplicates a Unicode string buffer of known length.

      :param data: Contents to duplicate.
      :param size: Length of ``data``, in ``wchar_t`` units.

   .. cpp:function:: string ( const std::wstring& data )

      Duplicates a standard wide-character string. Unicode is assumed.

      :param data: Contents to duplicate.

   .. cpp:function:: string ( const string& other )

      Duplicates an existing string buffer.

   .. cpp:function:: string ( size_type size )

      Builds a string buffer containing ``size`` copies of ``L'\0'``.

      This method is primarily useful for pre-allocating strings.

      :param size: Number of times to copy ``L'\0'``.

   .. cpp:function:: string ( size_type size, char_type filler )

      Builds a string buffer containing ``size`` copies of ``filler``.

      This method is primarily useful for pre-allocating strings.

      :param size: Number of times to copy ``filler``.
      :param filler: Filler character, copied ``size`` times.

   .. cpp:function:: ~string()

      De-allocates the string buffer's memory.

   .. cpp:function:: size_type size() const

      :returns: the number of characters in the string's buffer.

   .. cpp:function:: size_type length() const

      Alias for ``size()``, for compatibility with ``std::wstring``.

   .. cpp:function:: pointer data()

      .. note::

         Writing null characters in the string will **not** shorten it.

      .. warning:: The allocated memory will be freed by ``~string()``, do
         **not** ``delete[]`` it.

      :returns: a pointer to the internal character buffer.

   .. cpp:function:: const_pointer data() const

      .. warning:: The allocated memory will be freed by ``~string()``, do
         **not** ``delete[]`` it.

      :returns: a pointer to the internal character buffer.

   .. cpp:function:: swap ( string& rhs )

      Performs ``O(1)`` exchange of the contents of two strings.

      :param rhs: String with which contents should be exchanged.

   .. cpp:function:: void erase ( iterator begin, iterator end )

      Removes the range ``[begin,end)`` from the string.

      :param begin: First character to remove.
      :param end: One-past-the-last character to remove.

   .. cpp:function:: void resize ( size_type size )

      :param size: New string size.

      ``L'\0'``` is used as filler.

   .. cpp:function:: void resize ( size_type size, char_type filler )

      :param size: New string size.
      :param filler: Character to append if ``size > this->size()``.

   .. cpp:function:: iterator begin ()

      :returns: a RandomAccessIterator_ to the first ``wchar_t`` in the buffer.

   .. cpp:function:: iterator end ()

      :returns: a RandomAccessIterator_ to one-past-the-last ``wchar_t`` in the buffer.

   .. cpp:function:: const_iterator begin () const
   .. cpp:function:: const_iterator end () const

   .. cpp:function:: string& operator= ( const string& rhs )
   .. cpp:function:: string& operator= ( const_pointer rhs )
   .. cpp:function:: string& operator= ( const std::wstring& rhs )

   .. cpp:function:: char_type& operator[] ( size_type i )

      Obtains read-write acccess to the ``wchar_t`` at index ``i``.

      .. note::

         This is not necessarily the ``i`` the character.

      :param i: Index of the ``wchar_t`` to access.

   .. cpp:function:: char_type operator[] ( size_type i ) const

      Obtains the ``wchar_t`` at index ``i``.

      .. note::

         This is not necessarily the ``i`` the character.

      :param i: Index of the ``wchar_t`` to fetch.

   .. cpp:function:: operator std::wstring () const

      :returns: a ``std::wstring`` containing the same contents as ``*this``.

.. cpp:class:: string::box

   The :class:`string.box` class helps perform an optimization: when strings
   are allocated by the callee and caller-managed (as is typical with COM
   interfaces, for instance) and their de-allocation semantics are compatible
   with those expressed by the :class:`string` class, the string buffer may
   actually be managed directly instead of allocating an extra copy. This
   has both the benefit of being faster, it also reduces the risk of memory
   leaks.

   .. note::

      This class mainly serves as a proxy to distinguish directly manageable
      string buffers from normal string buffers, which require a copy, when
      passing them to the :class:``string`` constructor.

   .. cpp:function:: explicit box ( char_type * data )

      Builds a proxy, enabling a string to own ``data``.

      :param data: buffer who's ownership is to transfer.

   .. cpp:function:: box ( char_type * data, dword size )

      Builds a proxy, enabling a string to own ``data``.

      :param data: buffer who's ownership is to transfer.
      :param size: number of ``wchar_t`` items in the buffer.

   .. cpp:function:: dword size() const

      :returns: the number of ``wchar_t`` characters in the string.

      .. cpp:function:: wchar_t * data () const

      :returns: a pointer to the (mutable) data in the string buffer.


.. cpp:function:: bool operator== ( const string& lhs, const string& rhs )
.. cpp:function:: bool operator!= ( const string& lhs, const string& rhs )


.. [#] See the SGI design document discussing `representations of strings
    <http://www.sgi.com/tech/stl/string_discussion.html>`_ in the STL.

.. _RandomAccessIterator: http://www.sgi.com/tech/stl/RandomAccessIterator.html
.. _ReverseIterator: http://www.sgi.com/tech/stl/ReverseIterator.html
