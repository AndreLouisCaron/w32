.. _w32-sc-service:

#############################################
  :cpp:class:`w32::sc::Service` --- Service  
#############################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:class:: w32::sc::Service

   Background process with little or no user involvement.

   .. cpp:type:: void ( __stdcall * Context )( dword argc, wchar_t** argv )

      Prototype for a service's entry point function.

      .. note::

         This function does not return the service exit code. That value is set
         through the service status Handler.

   .. cpp:function:: Service ( Database database, string name, string path )

      :param database: Service database into which the service'll be registered.
      :param name: Name of the service, it must be unique.
      :param path: Absolute path to the service program's executable.

      Registers the executable at *path* as a service under *name* in
      *database*.

   .. cpp:function:: Service ( Database database, string name )

      :param database: Service database into which the service was registered.
      :param name: Name of the service.

      Opens a service registered under *name* in *database*.

   .. cpp:function:: void remove ()

      Uninstalls the service.

      Removes the service from the SCM. It will no longer be available for
      execution and must be re-installed in order to run again.


.. cpp:class:: w32::sc::Service::Handler

   Communication mechanism between the service process and service control
   manager.

   This object notifies the service control manager of status changes and
   receives status change requests from the service control manager 

   .. cpp:function:: Handler ( const string& service )

      :param name: Service name.

      Opens the service status handler.

   .. cpp:function:: ~Handler ()

      Changes the service status to @c stopped.

   .. cpp:function:: void signal () const

      Notifies the service database of the current status.

      .. note::

         This method is usually invoked in the service control handler in
         response to a service status interrogation. The service control
         periodically interrogates the service to monitor activity and report
         status accurately.

   .. cpp:function:: void signal ( const Status& status )

      :param status: Status to switch to.

      Changes the status and notifies the service database.

   .. cpp:function:: Status current () const

      :returns: The last indicated status.

      Obtains the current service status.

   .. cpp:function:: void exit ( dword code )

      :param code: Service process' exit status.

      Sets the service exit code. This does *not* kill the process.

   .. cpp:function:: virtual void stop ()
   .. cpp:function:: virtual void pause ()
   .. cpp:function:: virtual void resume ()
   .. cpp:function:: virtual void control ( int code )


.. cpp:class:: w32::sc::Service::Status

   Enumeration of possible service states.

   .. cpp:function:: static const Status stopped ()

      Indicates that the service is not running.

   .. cpp:function:: static const Status starting ()

      Indicates that the service has been requested to start but has not yet
      confirmed successful startup.

   .. cpp:function:: static const Status stopping ()

      Indicates that the service has been requested to stop but has not yet
      confirmed successful stop.

   .. cpp:function:: static const Status running ()

      Indicates that the service is currently running.

   .. cpp:function:: static const Status resuming ()

      Indicates that the service has been requested to resume execution after
      a period of inactivity, but has not yet confirmed successful wakeup.

   .. cpp:function:: static const Status pausing ()

      Indicates that the service has been requested to pause execution for a
      period of time, but has not yet confirmed successful sleep.


   .. cpp:function:: static const Status paused ()

      Indicates that the service is currently sleeping.

   .. cpp:type:: Value

   .. cpp:function:: Value value () const

      Obtains the native enumation value.

   .. cpp:function:: bool operator== ( const Status& rhs ) const
   .. cpp:function:: bool operator!= ( const Status& rhs ) const

