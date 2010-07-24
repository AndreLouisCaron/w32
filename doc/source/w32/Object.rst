.. _w32-object:

########################################################
  :cpp:class:`w32::mm::Object` --- Kernel-space Object  
########################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:class:: w32::Object

   .. cpp:type:: Handle

      Shared reference to the native system handle.

   .. cpp:function:: Object ( const Handle& handle )

      :param handle: The kernel object's handle.

   .. cpp:function:: Object ()

      .. note::

         This function is *never, ever* invoked because there is no other means
         than the parametric constructor to assign the object a handle. However,
         it is required because of virtual inheritance in some kernel objects.
         This seems to be a limitation of the language ensuring a default
         constructor to classes such as :cpp:class:`w32::Waitable`.

   .. cpp:function:: ~Object ()

      Releases the kernel object.

   .. cpp:function:: const Handle& handle () const

      :returns: The system handle for the kernel object.

   .. cpp:function:: void destroy ()

      Force premature release of the kernel object.
