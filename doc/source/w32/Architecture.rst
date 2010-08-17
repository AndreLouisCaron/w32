.. _w32-architecture:

############################################################
  :cpp:class:`w32::Architecture` --- Hardware architecture  
############################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:namespace:: w32

.. cpp:class:: Architecture

   :ref:`Enumeration <enumeration-concept>` of hardware architectures supported
   by Microsoft Windows.

   .. cpp:type:: Value

      Defines the enumerated values' type.

   .. cpp:function:: static Architecture of ( const System& system )

      Returns the :cpp:class:`Architecture` of a :cpp:class:`System`.

   .. cpp:function:: static const Architecture unknown ()

      Placeholder for any unknown hardware architecture.

   .. cpp:function:: static const Architecture x86 ()

      32-bit Intel architecture.

   .. cpp:function:: static const Architecture x64 ()

      64-bit AMD architecture and new 64-bit Intel architecture.

      .. seealso::

         :cpp:member:`ia64`

   .. cpp:function:: static const Architecture ia64 ()

      Old 64-bit Intel architecture (Itanium family).

      .. seealso::

         :cpp:member:`x64`

   .. cpp:function:: bool operator== ( const Architecture& rhs ) const

      Returns ``true`` if ``*this`` holds the same value as ``rhs`` does.

      .. seealso::

         :cpp:member:`operator!=`

   .. cpp:function:: bool operator!= ( const Architecture& rhs ) const

      Returns ``true`` if ``*this`` holds a value different from the one held by
       ``rhs``.

      .. seealso::

         :cpp:member:`operator==`

   .. cpp:function:: Value value () const

       Returns the native representation for the enumeration.

       .. seealso::

          :cpp:member:`operator Value`

   .. cpp:function:: operator Value () const

       Returns the native representation for the enumeration.

       .. seealso::

          :cpp:member:`value`
