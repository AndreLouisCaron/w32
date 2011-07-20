.. _w32-mt-list:

#################################################################
  :cpp:class:`w32::mt::List` --- Interlocked Singly Linked List  
#################################################################

.. cpp:namespace:: w32::mt

.. cpp:class:: w32::mt::List

   Attemp at a builtin thread-safe list. The MSDN documentation states:

      An interlocked singly linked list (SList) eases the task of insertion and
      deletion from a linked list. SLists are implemented using a nonblocking
      algorithm to provide atomic synchronization, increase system performance,
      and avoid problems such as priority inversion and lock convoys.

   However, the interface to this syncrhonization tool really sucks:

   * although it is called a singly-linked list, it has a stack's interface;
   * :cpp:func:`size` does not actually return the number of items in the list;
   * genericity through :cpp:type:`Item` is restrictive;
   * special care must be taken in memory allocation;
   * there is no support for automatic cleanup;
   * iterating over the items in the list is totally unsafe.

   If you're considering using this class to implement a producer-consumer
   scheme in, you might want to go along the lines of solutions proposed in
   `Lock-Free Queues <http://www.drdobbs.com/high-performance-computing/208801974>`_ and `Writing Lock-Free Code: A Corrected Queue <http://www.drdobbs.com/high-performance-computing/210604448>`_.

   .. cpp:type:: size_type

      Size of a list. Although this type is a 16-bit unsigned integer, more than
      2^16 items may be stored in the list: :cpp:func:`size` simply returns the
      number of elements modulus 65535.

   .. cpp:type:: Item

      List item header. There are basically two ways to use this:

      * Defined a ``struct`` with an ``Item`` as first member;

        .. code-block:: c++

           struct MyItem
           {
               w32::mt::List::Item header;
               // ...
           };

      * Derive from this ``struct``.

        .. code-block:: c++

           struct MyItem :
               w32::mt::List::Item header
           {
               // ...
           };

      The 2nd scenario is usually cleaner than the 1st because it doesn't
      require a ``reinterpret_cast`` when using :cpp:func:`push` and
      :cpp:func:`pop`; only a ``static_cast`` is required with :cpp:func:`pop`.

      .. warning::

         No matter which scenario, the ``struct`` may *never* contain
         ``virtual`` functions, because a pointer to the virtual table is
         stored at the beginning of the object. Yes, this sucks, but we're
         dealing with an interface for *The C Programming Language*, remember?
         If, however, you *are* used to writing C, you may use old-school
         function pointers to simulate ``virtual`` functions!

   .. cpp:type:: Data

      List header.

   .. cpp:type:: iterator
   .. cpp:type:: const_iterator

   .. cpp:member:: static w32::size_t alignment

      .. seealso::

         :cpp:class:`w32::mm::Alignment`

   .. cpp:function:: Data& data ()

      :returns: the list header.

   .. cpp:function:: const Data& data () const

      :returns: the list header.

   .. cpp:function:: size_type size ()

      :returns: the number of elements in the list, modulus 65535.

   .. cpp:function:: void push ( Item * item )

      Adds ``item`` to the front of the list.

      :param item: item to add to the list.

      .. note::

         ``item`` must be aligned on an :cpp:member:`alignment` boundary.

      .. seealso::

         :cpp:class:`w32::mm::Alignment`

   .. cpp:function:: Item * pop ()

      Removes the first item in the list.

   .. cpp:function:: Item * clear ()

      Removes all of the items in the list.

      :returns: a pointer to the first item in the list.

   .. cpp:function:: iterator begin ()
   .. cpp:function:: iterator end ()
   .. cpp:function:: const_iterator begin () const
   .. cpp:function:: const_iterator end () const

   .. warning::

      Although the :cpp:func:`push`, :cpp:func:`pop` and :cpp:func:`size`
      functions are atomic, :cpp:func:`begin` and :cpp:func:`end` are not.
      Moreover, the state of the list is not guaranteed to stay the same during
      iteration. If any iteration is performed, **all** forms of access must be
      synchronized using a :cpp:class:`w32::mt::Mutex` or other locking
      mechanism external to the list itself; this *really* renders this class
      utterly useless.
