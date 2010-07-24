.. _w32-sc-database:

###############################################################
  :cpp:class:`w32::sc::Database` --- Service control database  
###############################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:class:: w32::sc::Database

   Utility used to install, run and delete service programs.

   The service control manager is the mechanism used by the operating
   system to allow you to manage service programs. Service programs
   are virtual extensions to the operating system. These programs
   perform background work in a set-it-and-forget-it fashion: you
   install one, configure it and basically never deal with it again
   unless you want to delete the program. It can be configure to
   start automatically after you computer boots up and shutdown before
   your OS does (the usual case).

   .. cpp:function:: Database ()

      Open a connection to the SCM on the local machine.

      This gives you all-access rights to the service control manager,
      including installation, execution and removal of services. This
      usually requires the user executing the program to have system
      administration privilidges.

      :except AccessDenied: You do not have sufficient privilidges to get all-access rights to the SCM.

   .. cpp:function:: void run (const string& service, Service::Context context)

      :param service: Name of the service.
      :param context: User-supplied main function for the service.

      Executes the service.

      This function can only be executed from inside a process that was started
      by the SCM (it must be a service process). *service* is the name displayed
      in the SCM's user interface.
