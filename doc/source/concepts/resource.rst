.. _resource-concept:

########################################################
  Resource (Behavioral) --- Wrapper for System Objects  
######################################################## 
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

Intent
------
Ensure proper release of resources to the Operating System, and provided
high-level means to manipulate it.

Also Known As
-------------

Motivation
----------
Garbage collected environments generally provided a integrated management of
memory, but don't provide built-in means to automagically release *any* type of
resource. Some environments imitate the concept of C++ destructors with limited
success. This pattern emphasizes built-in, foolproof, management of all
resources.

Applicability
-------------

Structure
---------
See the code sample for the basic layout.

Participants
------------

Collaborations
--------------

Consequences
------------

Implementation
--------------

Sample Code
-----------

.. code-block:: c++

   #include <w32/Reference.hpp>

   class R
   {
      /* nested types. */
   public:
            // Holds an identifier as well as a variable deletion operator.
       typedef Reference<
         (implementation-defined), void(*)((implementation-defined)) > Handle;

       /* class methods. */
   public:
       static Handle proxy ((implementation-defined));
       static Handle claim ((implementation-defined));

           // Optional factory method(s), naming resource acquisition technique.
       static R create ( ... );
       // ...

       /* data. */
   private:
       Handle myHandle;

       /* construction. */
   public:
           // Primarily useful for creating resource proxies.
       explicit R ( const Handle& handle );

           // Primary resource creation mechanism.
       R ( ... );

       /* methods. */
   public:
       Handle handle () const;

       // ...
   };

Known Uses
----------
The :class:`w32.rgs.Key` uses this pattern to expose predefined hive keys,
refer to existing keys and create new keys. All keys are released along with
the preferred method.

Related Patterns
----------------
