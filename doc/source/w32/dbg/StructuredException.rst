.. _w32-dbg-structuredexception:

############################################################################
  :cpp:class:`w32::dbg::StructuredException` --- System-defined exceptions  
############################################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:namespace:: w32::dbg

.. cpp:class:: StructuredException

   Wrapper for Microsoft's structured exception handling (SEH).

   This helps a lot in debugging some low-level problems. It's role is
   to translate nitty gritty SEH into short and sweet reports of the
   problems that occur by translating the SEH errors into C++
   exceptions.

   .. cpp:type:: Filter

       ``_se_translator_function``

   .. cpp:function:: virtual const char * what const () = 0

      :returns: a description of the error.

   .. staticmethod:: const Filter translate ()

      Default SEH to C++ exception translation function.

      :raises: an exception of a type derived from this class.


.. cpp:class:: StructuredExpcetion::FilterReplacement

   Replaces the SEH to C++ translation function until the end of scope.

   .. cpp:function:: FilterReplacement ()

      Changes the SEH to C++ exception filter.

      :cpp:func:`translate` is used as the filter.

   .. cpp:function:: explicit FilterReplacement ( Filter filter )

      Changes the SEH to C++ exception filter.

      :param filter: Filter function to use as a replacement.

   .. cpp:function:: ~FilterReplacement ()

      Restores the previous SEH to C++ exception translator.
