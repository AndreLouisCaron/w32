.. _w32-sc-object:

#############################################################
  :cpp:class:`w32::sc::Object` --- Service control resource  
#############################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:class:: w32::sc::Object

   Encapsulates a resource in the service control manager.

   .. cpp:type:: Handle

      Holds the system identifier for the service control resource.

   .. cpp:function:: static Handle claim ( ::SC_HANDLE object )

      Returns a :cpp:class:`Handle` releasing *object* upon its destruction.

   .. cpp:function:: static Handle proxy ( ::SC_HANDLE object )

      Returns a :cpp:class:`Handle` abandonning *object* upon its destruction.

   .. cpp:function:: explicit Object ( const Handle& handle )

      Creates an owner for a :cpp:class:`Handle`.

   .. cpp:function:: const Handle& handle () const

      Obtains the :cpp:class:`Handle` owned by the service control resource.
