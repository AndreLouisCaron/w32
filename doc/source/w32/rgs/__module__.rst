.. _w32-rgs:

###################################################
  :mod:`w32::rgs` --- Using the Infamous Registry  
###################################################
.. sectionauthor:: Andre Caron <andre.l.caron@gmail.com>

.. module:: w32::rgs
   :synopsis: Using the infamous registry
.. moduleauthor:: Andre Caron <andre.l.caron@gmail.com>

This module provides services for manipulating the Windows registry. Although
most applications don't need to manipulate the registry, it is still useful for
task such as configuring COM components (Windows Explorer shell extensions come
to mind).

.. warning::

   Microsoft itself announces the Windows Registry as being deprecated and that
   its use is dangerous, having the potential to corrupt your -- or even worse,
   your *users'* -- computer(s).

Contents:

.. toctree::
   :maxdepth: 2

   Access.rst
   clean.rst
   Key.rst
   Keys.rst
   Type.rst
   Value.rst
   Values.rst
