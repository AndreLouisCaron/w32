.. _w32-time:

########################################
  :cpp:class:`w32::Time` --- Timestamp  
########################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:namespace:: w32

.. cpp:class:: w32::Time

   Wraps a ``::SYSTEMTIME`` structure.

   .. cpp:type:: Data

      ``::SYSTEMTIME``

   .. cpp:function:: static Time now ()

      :returns: a snapshot of the current time in the active locale.

   .. cpp:function:: Time ()

      Builds a dummy time object, ``0000/00/00 00:00:00``.

   .. cpp:function:: Time ( const Data& value )

      Creates a wrapper for a clone of ``value``.

      :param value: Value to contain.

   .. cpp:function:: Time ( const FILETIME& value )

      Converts a filesystem time to a system time instance.

      :param value: filesystem time to copy.

   .. cpp:function:: Data& data ()

      Obtains read-write access the native representation.

   .. cpp:function:: const Data& data () const

      Obtains read-only access the native representation.

   .. cpp:function:: word year () const
   .. cpp:function:: word month () const
   .. cpp:function:: word day () const
   .. cpp:function:: word hour () const
   .. cpp:function:: word minute () const
   .. cpp:function:: word second () const
   .. cpp:function:: word milliseconds () const
