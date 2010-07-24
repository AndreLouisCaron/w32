.. _w32-mm-global:

######################################################################
  :cpp:class:`w32::mm::Global` --- Global :cpp:class:`w32::mm::Heap`  
######################################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:class:: w32::mm::Global

   .. note::

      New applications should use the heap functions to allocate and manage
      memory unless the documentation specifically states that a global function
      should be used. For example, the global functions are still used with
      Dynamic Data Exchange (DDE), the clipboard functions, and OLE data
      objects.

   .. cpp:type:: Handle

      Kernel identifier for a memory block allocated by a local heap.

   .. cpp:function:: static Handle claim ( HGLOBAL object )

      :returns: a handle with a no-operation as a deallocation function.

      .. note::

         This function is primarily useful for compatibility with other APIs.

   .. cpp:function:: static Handle proxy ( HGLOBAL object )

      :returns: a handle with a real deallocation function.

      .. note::

         This function is primarily useful for compatibility with other APIs.

   .. cpp:function:: Global ( w32::size_t bytes )

      :param bytes: Size of the requeste memory block, in bytes.

      .. note::

         To access the requested memory block, see the :cpp:class:`Lock` class.

   .. cpp:function:: const Handle& handle () const

      :returns: the local memory object's system handle.

   .. w32::size_t size () const

      :returns: the current size of the memory block.

.. cpp:class:: w32::mm::Global::Lock

   Locks the memory block for use of the memory's contents.

   .. cpp:function:: explicit Lock ( Global& object )

      Locks ``object``, allowing you to access the contents of the memory.

      .. seealso::

         :cpp:func:`location`

   .. cpp:function:: ~Lock ()

      Releases the lock on the memory block. From this point on, you should not
      access the pointer returned by :cpp:func:`location` any longer.

   .. cpp:function:: void * location () const

      Obtains a pointer to the start of the memory block.
