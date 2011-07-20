.. _w32-ipc:

###################################################
  :mod:`w32::ipc` --- Inter-process Communication  
###################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. module:: w32::ipc
   :synopsis: Inter-process communication
.. moduleauthor:: Andre Caron <andre.l.caron@gmail.com>

This module provides services for interoperating with other processes.

.. note::

   Despite its name, this module mainly provides services for process management
   and *initiating* communication with other processes. Most inter-process
   communication is actually done using services from the :mod:`w32.io` and
   :mod:`w32.mt` modules because explicit support for those services is done
   through the kernel, already enabling inter-process communication. The
   :mod:`w32.net` module also provides (by definition) inter-process
   communication with the same (local) or another (remote) computer.

Contents:

.. toctree::
   :maxdepth: 2
