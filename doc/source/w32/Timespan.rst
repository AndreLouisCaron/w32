.. _w32-timespan:

###################################################
  :cpp:class:`w32::Timespan` --- Duration in time  
###################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:namespace w32

.. cpp:class:: w32::Timespan

   Encodes a length of time in system counter "ticks".

   .. cpp:type:: Value

      Unsigned integer multiple of the quantum unit. For obvious backward
      compatibility reasons, this is a number of milliseconds, regardless of the
      actual quantum your hardware may provide.

   .. cpp:function:: static Timespan infinite ()

      Obtains a value representing an infinite amount of time.

   .. cpp:function:: Timespan ()

      Builds a null (empty) timespan (0 in any kind of units).

   .. cpp:function:: Timespan ( Value ticks )

      :param ticks: Number of ticks the timespan should represent.

   .. cpp:function:: Timespan ( Value ticks, const Unit& unit )

      :param ticks: Number of ``unit`` times the timespan should represent.
      :param unit: Unit used for ``ticks``.

   .. cpp:function:: bool empty () const

      :returns: ``true`` if the timespan equals 0 ticks.

   .. cpp:function:: Value ticks () const

      .. note::

         Native units are the lowest possible resolution the system recognizes.
         It is a common denominator: any timespan can be expressed using an
         integer multiple of this unit.

      :returns: unsigned integer multiple of ticks the timespan represents.

   .. cpp:function:: double get ( const Unit& unit ) const

      .. note::

         This method returns a floating-point value because the timespan may not
         be an integer of multiple ``unit`` (``unit`` might be longer than
         ``*this`` in duration).

      :returns: duration of the timespan in multiples of ``unit``.


.. cpp:class:: w32::Timespan::Unit

   Enumeration of common time span reference units.

   .. cpp:function:: static const Unit native ()
   .. cpp:function:: static const Unit millisecond ()
   .. cpp:function:: static const Unit second ()
   .. cpp:function:: static const Unit minute ()
   .. cpp:function:: static const Unit hour ()
   .. cpp:function:: static const Unit day ()
   .. cpp:function:: static const Unit week ()

   .. cpp:function:: Value ticks () const

      :returns: Unsigned integer multiple of the quantum.

   .. cpp:function:: Unit& operator*= ( Value factor )
   .. cpp:function:: Unit& operator*= ( double factor )
