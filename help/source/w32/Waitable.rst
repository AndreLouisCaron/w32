.. _w32-waitable:

###############################################################
  :cpp:class:`w32::Waitable` --- Basic synchronization object  
###############################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:class:: w32::Waitable

   Represents an object that can by used for synchnization by waiting for a
   certain state to be reached.

   .. warning::

      This interface is **not** designed to be used directly by user code.
      It is designed for code re-use and classification only. It's methods are
      not made public because the resulting hierarchy wouldn't respect the
      LiskovSubstitutionPrinciple_: no common name is suitable for all waitable
      objects and some abstractions convey resource acquisition semantics to
      :meth:`wait` and :meth:`test`.

   .. cpp:function:: bool wait () const

      Waits *indefinitely* for the signalling of the waitble object.

      :returns: ``true`` if the object is, or just entered, the *signaled* state

   .. cpp:function:: bool wait ( Timespan timeout ) const

      :param timeout: Amount of time to wait before abandonning synchronization attemp.
      :returns: ``true`` if the object is, or just entered, the *signaled* state.

   .. cpp:function:: bool test () const

      :returns: ``wait(Timespan())``.

.. cpp:class:: w32::Waitable::Timeout

   Thrown to signal an expected wait time out.

   Scoped locks acquire a resource in their constructor and cannot
   return a success value. This is thrown to prevent the guarded
    block's execution.


.. _LiskovSubstitutionPrinciple: http://en.wikipedia.org/wiki/Liskov_substitution_principle
