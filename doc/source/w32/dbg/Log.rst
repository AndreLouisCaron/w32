.. _w32-dbg-log:

########################################################
  :cpp:class:`w32::dbg::Log` --- Application event log  
########################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:namespace:: w32::dbg

.. cpp:class:: w32::dbg::Log

    Persistant, standard, localizable, logging mechanism.

    .. note::

        In order to be used properly, the event log needs to be registered when
        the application is installed (don't forget to unregister it when
        uninstalling, your users will appreciate it :-).

   .. cpp:type:: Handle

   .. cpp:function:: static Handle claim ( HANDLE object )

      Creates a handle that will eventually release ``object``.

   .. cpp:function:: static Handle proxy ( HANDLE object )

      Creates a handle that will never release ``object``.

   .. cpp:function:: static void install ( const string& name, const string& path, const string& categories, dword count )

      :param name: name of the event source to install.
      :param path: path to the message-only DLL containing string resources.
      :param categories: path to the resource-only DLL containing application-defined message category definitions.
      :param count: numer of application-defined message categories.

   .. cpp:function:: static void remove ( const string& name )

      :param name: Name of the event source to uninstall.

   .. method:: Log ( const Handle& handle )

      Creates a wrapper for an externally allocated event log handle.

      :param handle: event log handle.

   .. method:: Log ( const string& name )

      Opens an application event log.

      :param name: event log name.

   .. method:: const Handle& handle () const

      :returns: the event log's handle.

   .. method:: void Log::report ( const Event& event )

      :param event: Event to store in the persistent event log.
