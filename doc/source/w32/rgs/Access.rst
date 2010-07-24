.. _w32-rgs-access:

##########################################################
  :cpp:class:`w32::rgs::Access` --- Registry Access Mask  
##########################################################

.. cpp:class:: w32::rgs::Access

   :ref:`Enumeration <enumeration-concept>` of registry access restrictions.

   Key access restrictions are applied on a per-handle basis, and only when
   opening an existing key. The system may refuse access to certain keys for
   security reasons. For instance, write access to ``HKEY_LOCAL_MACHINE`` is not
   granted unless the process is running with elevated priviledges. If you only
   want to determine if a certain product is installed, you may probably
   enumerate ``HKEY_LOCAL_MACHINE\SOFTWARE`` by requesting access using
   :cpp:func:`w32::rgs::Access::read()` only.

   .. cpp:type:: Value

      Native access mask representation.

   .. cpp:function:: static const Access list ()

      Permission to enumerate sub-keys and values.

   .. cpp:function:: static const Access get ()

      Permission to get values.

   .. cpp:function:: static const Access set ()

      Permission to add, change and remove values.

   .. cpp:function:: static const Access create ()

      Permission to create and delete sub-keys.

   .. cpp:function:: static const Access read ()

      :cpp:func:`w32::rgs::Access::list` and :cpp:func:`w32::rgs::Access::get`.

   .. cpp:function:: static const Access write ()

      :cpp:func:`w32::rgs::Access::set` and
      :cpp:func:`w32::rgs::Access::create`.

   .. cpp:function:: static const Access all ()

      All-access permision! This is the default for newly created keys.

   .. cpp:function:: bool operator== ( const Access& rhs ) const

      Returns ``true`` if ``*this`` holds the same value as ``rhs`` does.

      .. seealso::

         :cpp:func:`w32::rgs::Access::operator!=`

   .. cpp:function:: bool operator!= ( const Access& rhs ) const

      Returns ``true`` if ``*this`` holds a value different from the one held by
       ``rhs``.

      .. seealso::

         :cpp:func:`w32::rgs::Access::operator==`

   .. cpp:function:: w32::rgs::Acces::Value value () const

       Returns the native representation for the enumeration.

       .. seealso::

          :cpp:func:`w32.Access.operator Value`

   .. cpp:function:: operator w32::rgs::Acces::Value () const

       Returns the native representation for the enumeration.

       .. seealso::

          :cpp:func:`w32.Access.value`
