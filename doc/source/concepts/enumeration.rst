.. _enumeration-concept:

#########################################################
  Enumeration (Creational) --- Set of Predefined Values  
#########################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

Intent
------
Declaration of a fixed, known *apriori*, set of values.

Also Known As
-------------

Motivation
----------
The ``enum`` construct, as defined in many languages, is simply insufficient
to support the enumeration of arbitratry values. In particular, C++'s ``enum``
may not contain user-defined types.

Applicability
-------------
Inherently, you may apply this pattern when you wish to enumerate a set of items
at compile-time and allow clients to create variables referring to any of those
in the set.

Structure
---------
See the code sample for the basic layout.

Participants
------------

Collaborations
--------------

Consequences
------------
It is difficult not to break existing code when adding values *aposteriori*
because existing clients have been told the list of values was exhaustive.

Implementation
--------------
Avoid using static instances in enumeration classes exported through a DLL
interface because some compilers won't initialize class variables when loading
the DLL; prefer ``static`` fonctions to ``static`` variables, ``private`` or
``public``. This also grants you the flexibility of implementing lazy
initialization.

If the ``Value`` type is too heavy-weight, prefer indirection through a pointer,
so as to create fast and cheap copies of enumeration instances, as well as
simplifying the comparison operators (they may now be compare internal values by
identity).

Input and output operators are optional, but greatly simplify debugging.

Sample Code
-----------

.. code-block:: c++

   class E
   {
      /* nested types. */
   public:
          // May hold a pointer to a heavy-weight structure for optimization.
       typedef (implementation-defined) Value;

      /* class data. */
   public:
           // Factory methods: each provides one of the enumerated values.
           // Values may be build before hand with static, or even lazy,
           // initialization, and then copied by these methods.
       static const E a ();
       static const E b ();

       // ... more enumerated values ...

       /* data. */
   private:
       Value myValue;

       /* construction. */
   private:
           // For internal use only.
       E ( Value value );

       /* methods. */
   public:
       Value value () const;

       // ...

       /* operators. */
   public:
           // Allow easy extraction of nested value.
       operator Value () const;
   };

   bool operator== ( const E&, const E& );
   bool operator!= ( const E&, const E& );

   std::ostream& operator<< ( std::ostream&, const E& );
   std::istream& operator>> ( std::istream&, E& );

Known Uses
----------
The :class:`w32.rgs.Key` exposes a variant of the pattern, creating proxies to
the registry hives predefined by Microsoft. This is also an example of
enumeration that adds values depending on the Windows version.

Related Patterns
----------------

