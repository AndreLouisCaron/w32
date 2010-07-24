.. _w32-module:

########################################################
  :cpp:class:`w32::Module` --- Native executable image  
########################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:namespace:: w32

.. cpp:class:: w32::Module

   Native executable image; this covers both executables (EXE) and
   dynamically-linked librairies (DLL). This class allows refering to loaded
   modules, including the current module, as well as loading external modules
   at run-time.

   .. cpp:type:: Handle

      Garbage-collected reference to the native handle.

   .. cpp:function:: static Handle claim ( HMODULE object )

      :param object: Existing module handle.
      :returns: A handle that will release ``object``.

   .. cpp:function:: static Handle proxy ( HMODULE object )

      :param object: Existing module handle.
      :returns: A handle that will not release ``object``.

   .. cpp:function:: static Module load ( string path )

      .. note::

         The loading is subjec to library search paths when using only a file
         name. If you know where the module can be found, providing the absolute
         path is safer.

      :param path: Executable or dynamic library file path.
      :returns: A fully loaded module.
      :raises UncheckedError: The requested module was not loaded.

   .. cpp:function:: Module ( const Handle& handle )

      Creates a wrapper object for an existing handle.

      .. seealso::

         :cpp:func:`w32::Module::claim`
         :cpp:func:`w32::Module::proxy`

      :param handle: Existing handle.

   .. cpp:function:: Module ()

      Creates a wrapper for the current process's executable.

   .. cpp:function:: Module ( const string& name )

      Locates an already loaded

      :raises UncheckedError: The requested module was not loaded.

   .. cpp:function:: const Handle& handle () const

      Obtains the module's ``Handle``.

   .. cpp:function:: string name () const

      Obtains the module's file name.

   .. cpp:function:: string path () const

      Obtains the module's absolute path.

   .. cpp:function:: void * get ( const astring& symbol ) const

      Obtains a raw pointer to a DLL-exported symbol.

      :param symbol: The requested symbol's name.
      :returns: A pointer to the requested symbol, or a null pointer.

   .. cpp:function:: T get<T> ( const astring& symbol ) const

      Obtains a typed pointer to a DLL-exported symbol. ``Pointer`` may be a
      function signature.

      :param symbol: The requested symbol's name.
      :returns: A pointer to the requested symbol, or a null pointer.

   .. cpp:function:: void * load ( const astring& symbol ) const

      Obtains a raw pointer to a DLL-exported symbol.

      :param symbol: The requested symbol's name.
      :returns: A pointer to the requested symbol.
      :raises UncheckedError: No symbol with that name is exported by the module.
   .. cpp:function:: T load<T> ( const astring& symbol ) const

      Obtains a typed pointer to a DLL-exported symbol.

      :param symbol: The requested symbol's name.
      :returns: A pointer to the requested symbol.
      :raises UncheckedError: No symbol with that name is exported by the module
