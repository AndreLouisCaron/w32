.. _w32-rgs-clean:

##############################################################
  :cpp:func:`w32::rgs::clean` --- Recursively remove entries  
##############################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:namespace:: w32::rgs

.. cpp:function:: void w32::rgs::clean ( const w32::rgs::Key& root )

   :param root: Key for which all sub-keys and values will be removed.

   Recursively removes all entries under ``root``.

   .. note::

      ``root`` itself is not removed. This function is designed to remove an
      entire tree of registry keys when the key itself is "owned" by some other
      entity (i.e. remove shell extension registration entries associated to
      a particular file type and leave the file association key itself
      unharmed).
