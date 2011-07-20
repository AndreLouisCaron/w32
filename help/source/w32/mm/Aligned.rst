.. _w32-mm-aligned:

################################################################
  :cpp:class:`w32::mm::Aligned` --- Boundary-aligned allocator  
################################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:namespace:: w32

.. cpp:class:: w32::mm::Aligned

   Some particular hardware operations mandate the use of *aligned* memory
   blocks. Typical requests are ``dword``-aligned memory. This is normally
   required when the hardware performs specific optimizations on pointers. One
   possible use of ``dword``-aligned (multiples of 4) pointers is to increase
   the total addressable amount of memory (the lower 2 bits are always 0, so
   the address may be shifted, resulting in 4 times the amount of addressable
   memory).

   .. note::

      Do not use this allocation scheme unless a particular API requests it.

   .. cpp:function:: static bool supports ( w32::size_t alignment )

      :param alignment: Boundary on which allocation should be aligned.
      :returns: ``true`` if ``alignment`` is a non-zero power of two.

      Validates that the system supports the requested alignment.

   .. cpp:function:: Aligned ( w32::size_t alignment )

      :param alignment: Requested memory boundary.

      Builds an allocator that will allocate memory blocks aligned on
      boundaries of a multiple of ``alignment``.

      .. seealso::

         :cpp:func:`w32::mm::Aligned::supports`

   .. cpp:function:: w32::size_t alignment () const

      
