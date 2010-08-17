.. _w32-mm-local:

####################################################################
  :cpp:class:`w32::mm::Local` --- Local :cpp:class:`w32::mm::Heap`  
####################################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:class:: w32::mm::Local

   .. note::

      New applications should use the heap functions unless the documentation
      specifically states that a local function should be used. For example,
      some Windows functions allocate memory that must be freed with
      ``LocalFree()``.

   .. cpp:type:: Handle

      Kernel identifier for a memory block allocated by a local heap.

   .. cpp:function:: static Handle claim ( HLOCAL object )

      :returns: a handle with a no-operation as a deallocation function.

      .. note::

         This function is primarily useful for compatibility with other APIs.

   .. cpp:function:: static Handle proxy ( HLOCAL object )

      :returns: a handle with a real deallocation function.

      .. note::

         This function is primarily useful for compatibility with other APIs.

   .. cpp:function:: Local ( w32::size_t bytes )

      :param bytes: Size of the requeste memory block, in bytes.

      .. note::

         To access the requested memory block, see the :cpp:class:`Lock` class.

   .. cpp:function:: const Handle& handle () const

      :returns: the local memory object's system handle.

   .. w32::size_t size () const

      :returns: the current size of the memory block.

.. cpp:class:: w32::mm::Local::Lock

   Locks the memory block for use of the memory's contents.

   .. cpp:function:: explicit Lock ( Local& object )

      Locks ``object``, allowing you to access the contents of the memory.

      .. seealso::

         :cpp:func:`location`

   .. cpp:function:: ~Lock ()

      Releases the lock on the memory block. From this point on, you should not
      access the pointer returned by :cpp:func:`location` any longer.

   .. cpp:function:: void * location () const

      Obtains a pointer to the start of the memory block.
