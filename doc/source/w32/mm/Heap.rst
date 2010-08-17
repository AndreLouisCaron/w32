.. _w32-mm-heap:

###################################################
  :cpp:class:`w32::mm::Heap` --- Simple allocator  
###################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:class:: w32::mm::Heap

    .. attention::

       Using a private heap for allocation memory in fixed-size blocks can
       reduce memory fragmentation and increase allocation speed considerably.
       Moreover, if always used by a single thread, synchronization can be
       disabled, further increasing speed.

   .. cpp:type:: Handle

      Owns the heap resource.

   .. cpp:function:: Heap ()

   .. cpp:function:: ~Heap ()

      Reclaims all memory allocated by the heap, returning the virtual memory
      pages to the system. This is the key to reducing memory fragmentation.

   .. cpp:function:: void * acquire ( size_t amount )

      :param amount: Size of the requested chunk, in bytes.
      :returns: A pointer to the first byte in the chunk.

      Performs allocation of `amount` bytes of memory.

   .. cpp:function:: void release ( void * chunk, size_t amount )

      :param chunk: Pointer to the first byte in the chunk.
      :param amount: Size of the chunk of memory, in bytes.

   .. cpp:function:: void compact ()

      Compacts memory in the heap by coalescing adjacent freed blocks of memory,
      reducing memory fragmentation.

      .. note::

         The heap is automatically compacted when memory is freed. This function
         is only useful if you disable memory compacting for the entire system
         (see Debugging Tools for Windows).

   .. cpp:function:: dword flags () const

      :returns: Flags set at heap creation (always 0 for the default heap).


.. class:: w32::mm::Heap::Lock

   Acquires the critical section associated with the heap, preventing other
   threads from allocating memory.

   This mechanism is useful when walking the heap, because it prevents other
   threads from modifying the heap while it its entries are being enumerated.

   .. warning::

      Results are undefined for locking attempts on heaps for which
      serialization was disabled (never applies to the default heap).

   .. cpp:function:: Lock()
   .. cpp:function:: ~Lock()


.. cpp:class:: w32::mm::Heap::Walker

   Enumerator for heap entries.

   .. warning::

      You should lock the heap before you enumerate its entries.

   .. cpp:function:: Walker ( const Heap& heap )

      Walks the given heap.

   .. cpp:function:: Entry& entry ()
   .. cpp:function:: const Entry& entry () const
   .. cpp:function:: bool next ()

      :returns: If finished, ``false``.

      Walks up to the next heap entry.

      .. note::

         The first result is obtained be the constructor, use it before
         calling this method. It is best to use a `do`-loop to enumerate heap
         entries.


.. class:: w32::mm::Heap::Entry

   .. cpp:type:: Data

      Native representation.

   .. cpp:function:: Entry ()
   .. cpp:function:: Data& data ()
   .. cpp:function:: const Data& data () const
   .. cpp:function:: bool busy () const
   .. cpp:function:: bool moveable () const
