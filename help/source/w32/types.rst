.. _w32-types:

########################
  Native integer types  
########################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:namespace:: w32

.. :cpp:type:: uint

   ``unsigned int``

.. :cpp:type:: ulong

   ``unsigned long``

.. :cpp:type:: pointer

   Opaque pointer.

.. :cpp:type:: size_t

   Unsigned integer type, with ``sizeof(size_t) == sizeof(pointer)``.

.. :cpp:type:: byte

   Smallest addressable unit in memory: unsigned 8-bit integer.

.. :cpp:type:: word

   Machine word: unsigned 16-bit integer.

.. :cpp:type:: dword

   Double machine word: unsigned 32-bit integer.

.. :cpp:type:: qword

   Quadruple machine word: unsigned 32-bit integer.

.. :cpp:type:: int8

   Signed 8-bit integer.

.. :cpp:type:: uint8

   Unsigned 8-bit integer.

.. :cpp:type:: int16

   Signed 16-bit integer.

.. :cpp:type:: uint16

   Unsigned 16-bit integer.

.. :cpp:type:: int32

   Signed 32-bit integer.

.. :cpp:type:: uint32

   Unsigned 32-bit integer.

.. :cpp:type:: int64

   Signed 64-bit integer.

.. :cpp:type:: uint64

   Unsigned 64-bit integer.

.. :cpp:type:: intptr

   Integer the size of a pointer. Used for pointer arithmetic.

.. :cpp:type:: uintptr

   Integer the size of a pointer. Used for pointer arithmetic.

.. :cpp:type:: ulongptr

   Integer the size of a pointer. Used for pointer arithmetic. This is the
   previledged type for portable code between 32-bit and 64-bit machines as the
   compiler expands it to the proper size.
