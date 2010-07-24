.. _w32-mm-allocator:

#####################################################################
  :cpp:class:`w32::mm::Allocator` --- Abstract allocator definition  
#####################################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:class:: w32::mm::Allocator

   .. cpp:function:: virtual ~Allocator ()
   .. cpp:function:: virtual void * acquire ( size_t amount ) = 0
   .. cpp:function:: virtual void release ( void * start size_t amount ) = 0
