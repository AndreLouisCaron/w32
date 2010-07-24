.. _w32-system:

###################################################
  :cpp:class:`w32::System` --- System information  
###################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:namespace:: w32

.. cpp:class:: w32::System

   Describes a running system.

   .. cpp:type:: Data

      Backend structure, used by the system to return us information.

   .. cpp:function:: System()

      Obtains information about the system running the current process.

   .. cpp:function:: Data& data ()

      Read-write access to the native structure.

   .. cpp:function:: const Data& data () const

      Read-only access to the native structure.

   .. cpp:function:: Architecture architecture () const

      Obtains the system's :class:`w32.Architecture`.

   .. cpp:function:: dword pagesize () const

      Obtains the system's page size.

   .. cpp:function:: dword processors () const

      Obtains the number of processors.
