.. _w32-version:

##########################################################
  :cpp:class:`w32::Version` --- Operating system version  
##########################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. cpp:namespace:: w32

.. cpp:class:: w32::Version

   Enumerates

   .. cpp:type:: Data

      Backend structure, used by the system to return us information.

   .. cpp:function:: static const Version _2000 () const

      Windows 2000.

   .. cpp:function:: static const Version xp () const

      Windows XP.

   .. cpp:function:: static const Version vista () const

      Windows Vista.

   .. cpp:function:: Version()

      Obtains information about the system running the current process.

   .. cpp:function:: Version(dword major, dword minor)

      Creates a structure defining the major and minor version numbers.

      .. note::

          The resulting structure is incomplete. This is normally used for
          performing version validation.

   .. cpp:function:: Data& data ()

      Read-write access to the native structure.

   .. cpp:function:: const Data& data () const

      Read-only access to the native structure.

   .. cpp:function:: dword major () const

      Obtains the system's major version number.

   .. cpp:function:: dword minor () const

      Obtains the system's minor version number.

   .. cpp:function:: dword build () const

      Obtains the system's build number.

   .. cpp:function:: bool operator== ( const Version& rhs ) const

      Checks if two versions have the same ``major()`` and ``minor()`` numbers.

   .. cpp:function:: bool operator< ( const Version& rhs ) const

      Checks if two versions have the same ``major()`` and ``minor()`` numbers.
