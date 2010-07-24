.. _authoring-a-service-application:

Authoring a Service Application
===============================

A full-blown service application might look like the following:

.. code-block:: c++

   namespace {
       
           // Custom service events. These are accompanied by a "message-only"
           // dynamically-linked library. You may also register a single event
           // class with a single string parameter and format all messages
           // yourself, but the message-only DLL helps with translations!
       class ServiceStartup : public w32::dbg::Event { /*...*/ };
       class ServiceShutdown : public w32::dbg::Event { /*...*/ };
       class DebuggingError : public w32::dbg::Event { /*...*/ };
       
       const wchar_t ServiceName[] = L"My 1st C++ Service";
       
       void __stdcall service ( w32::dword argc, wchar_t ** argv )
       try
       {
           w32::Service::Handler handler;
           w32::Service::Status status(ServiceName, handler);
           
               // Technically speaking, the log name could be different from the
               // service name, but it's more intuitive to use the same. Note
               // That it is normally part of your installation procedure to
               // register the event source under this name...
           w32::dbg::Log log(ServiceName);
           log.report(ServiceStartup(ServiceName));
           
           try {
                   // This is not the only way to write the service's
                   // "quasi-infinite" loop, but you should check the service
                   // status on a periodic basis. Your may also write a custom
                   // handler and fire an event, then WaitForMultipleObjects()
                   // or anything along those lines.
               do {
                   /*****************************/
                   // YOUR _REAL_ SERVICE CODE. //
                   /*****************************/
               }
                while ( status.running() );
           }
               // Error with an API call.
           catch ( w32::dbg::UncheckedError& error ) {
               log.report(DebuggingError(error));
           }
               // Access violation or division by zero and the like.
           catch ( w32::dbg::UncheckedError& error ) {
               log.report(DebuggingError(error));
           }
               // Make sure we catch everything we can.
           catch ( ... ) {
               log.report(DebuggingError(L"Caught unknown exception!"));
           }
           
           log.report(ServiceShutdown(ServiceName));
       }
           // Probably failed acquiring the event log. In any case, we can't
           // report anything without an event log; just don't crash!
       catch ( ... ) {}
   
   }
   
   #include <w32/console-program.hpp>
   namespace {
   
       int run ( int argc, wchar_t ** argv )
       {
           // Could deduce other things to do based on arguments.
           // Typically, no args means: run!
           
               // Ask to switch to service context. This will fail if the
               // process is not started by the service control manager!
           Database().run(::ServiceName, &::service);
       }
   }
   #include <w32/console-program.cpp>
