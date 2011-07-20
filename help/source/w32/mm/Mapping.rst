.. _w32-mm-mapping:

############################################################
  :cpp:class:`w32::mm::Mapping` --- In-memory File Mapping  
############################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:class:: w32::mm::Mapping

   Segment of virtual memory to which is assigned a byte-for-byte correlation
   with some portion of a file.

   Memory-mapped files lead to increased I/O performance, especially for smaller
   files. For starters, reading from memory is faster than using a system call
   to read a portion of a file. Moreover, the mapped region is the kernel's page
   cache, avoiding a copy of the data in user space.

   .. cpp:function:: Mapping ( fs::File& file, Mode mode, qword size )

      :param file: The file that will be mapped into memory.
      :param size: Total size of the file to map.

      Reserves one or more pages of memory for a file mapping. If ``size`` is 0,
      the entire file will be mapped.

   .. cpp:function:: Mode mode () const

.. cpp:class:: w32::mm::Mapping::Mode

   :ref:`Enumeration <enumeration-concept>` of file mapping modes.

   .. cpp:type:: Value

      Native mapping mode representation.

   .. cpp:function:: static const Mode i ()

      Maps a file into memory as read-only.

   .. cpp:function:: static const Mode o ()

      Maps a file into memory as write-only.

   .. cpp:function:: Value value () const

      :returns: the native representation of the mapping mode.

   .. cpp:function:: operator Value () const

      :returns: the native representation of the mapping mode.

.. cpp:class:: w32::mm::Mapping::View

   Selection of what portion to map into memory.

   .. cpp:function:: View ( Mapping& mapping, qword offset=0, dword amount=0 )

      Maps a portion of the file to a page of memory.

      The file mapping actually only reserves an area in memory. A view of the
      file maps the contents of the file onto that reserved page.

      :param mapping: File mapping object backing the view.
      :param offset: Offset, in bytes, from the start of the file.
      :param amount: Number of bytes to map. If this is 0, 

      If ``amount``  is 0, all bytes starting from ``offset``, are mapped into
      memory.

   .. cpp:function:: ~View ()

      Unmaps the file from the reserved page.

   .. cpp:function:: void * location ()

      Obtains the base address for the view.

   .. cpp:function:: void flush ( dword amount = 0 )

      Write to disk to reflect the contents of memory.

      No metter the amount to flush, the commit range always starts at the base
      of the view. If ``amount`` is 0 (the default), all of the view is
      commited.

      :param amount: Number of bytes, starting from the base of the view, to commit to disk.
