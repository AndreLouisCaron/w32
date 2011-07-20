.. _w32-rgs-type:

#######################################################
  :cpp:class:`w32::rgs::Type` --- Registry Value Type  
#######################################################

.. cpp:class:: w32::rgs::Type

   :ref:`Enumeration <concept_Enumeration>` of registry value types.

   .. cpp:type:: Value

      Native type code representation.

   .. cpp:function:: static const Type dword ()

      32-bit non-negative integer.

   .. cpp:function:: bool operator== ( const Type& rhs ) const

      :returns: ``true`` if ``*this`` holds the same value as ``rhs`` does.

      .. seealso::

         :cpp:func:`w32::rgs::Type::operator!=`

   .. cpp:function:: bool operator!= ( const Type& rhs ) const

      :returns: ``true`` if ``*this`` holds a value different from the one held by ``rhs``.

      .. seealso::

         :cpp:func:`w32::rgs::Type::operator==`

   .. cpp:function:: w32::rgs::Acces::Value value () const

       :returns: the native representation for the enumeration.

       .. seealso::

          :cpp:func:`w32.Type.operator Value`

   .. cpp:function:: operator w32::rgs::Acces::Value () const

       :returns: the native representation for the enumeration.

       .. seealso::

          :cpp:func:`w32.Type.value`
