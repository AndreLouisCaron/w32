.. _w32-dbg-event:

######################################################
  :cpp:class:`w32::dbg::Event` --- Application event  
######################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:namespace:: w32::dbg

.. cpp:class:: w32::dbg::Event

   Persistant, standard, localizable, logging mechanism.

   .. cpp:type:: Category

      ``word``

   .. cpp:type:: Message

      ``dword``

   .. cpp:function:: virtual Type type () const = 0

      :returns: system-defined event category identifier.

   .. cpp:function:: virtual Category category () const = 0

      :returns: application-defined event category identifier.

   .. cpp:function:: virtual word argc () const

      :returns: argument count

   .. cpp:function:: virtual const wchar_t ** argv () const

      :returns: argument values


.. cpp::class:: w32::dbg::Event::Type

   Enumeration of system-wide event categories.

   .. cpp:type:: Value

      ``word``

   .. staticmethod:: const Type information ()

      Regular notification, should be used by default.

   .. staticmethod:: const Type success ()

      Indicates a noteworthy event.

   .. staticmethod:: const Type error ()

      Indicates failure to accomplish some action.

   .. staticmethod:: const Type warning ()

      Indicates failure to accomplish some optional action.

   .. cpp:function:: Value value () const

      :returns: The native code representing the type.
