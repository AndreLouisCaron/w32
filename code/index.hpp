// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

/*!
 * @mainpage w32++ Project
 *
 * The w32++ project aims at defining a @e modern C++ API for Win32.
 *
 *
 * @section portability Why use a intentionnally non-portable API?
 *
 * @subsection true-portability True portability
 *
 * Portability is achieved through making non-portable code easy to write.  Many
 * other development environments, libraries and programming languages will try
 * to make you believe that you can run the same code on any platform without
 * writing @e any non-portable code.  First, this can only be achieved for a
 * limited set of applications because it relies on defining the project in
 * terms of only features common to all systems.  This is why the C++ standard
 * library doesn't contain networking and graphical user interface facilities
 * (for example).  Second, when it @e is achieved, it is usually done in a way
 * that is disrespectful of users.  Java graphical user interfaces look wrong on
 * all platforms.  They have a default look and feel that is specific to Java
 * applications.  Although there is support for "native" look and feel settings,
 * these completely ignore any customization at the operating system level and
 * window manager.
 *
 * @subsection common-denominator Common denominator
 *
 * Moreover, some software cannot be expressed in terms of portable features.
 * Most software requires an installation procedure, which is anything but even
 * similar between platforms.  Some installer generator software produce
 * platform-specific installers using a single "portable" product description.
 * These are often far inferior to native installer capabilities.  For instance,
 * the Microsoft Installer (MSI) provides automatic installer rollback using
 * kernel-level transactions for writing to the registry and filesystem.  This
 * is an important feature for non-technical end-users when installation fails.
 *
 * @subsection system-applications Inherently non-portable applications
 *
 * Finally, some software is not destined to be portable at all.  Drivers,
 * virus/malware protection software, system cleanup, etc. is inherently tied to
 * the targetted system (often even specialized for each version).  Such
 * software needs access to all features provided by the host system to be
 * effective and cannot be restricted to any common denominator.
 *
 * @subsection local-extensions Using local extensions
 *
 * Of course, there is always the occasional power user that chose a particular
 * system because of the extensions it provides.  If the development tools you
 * use to build your software cannot take advantage of this investment, then
 * this user will be displeased.
 *
 * @subsection leaky-abstractions Leaky abstractions
 *
 * In short, the whole concept of writing 0 lines of non-portable code in a
 * project is short-sighted.  The aim is to make developers' lives easier at the
 * expense of the user.  In the end, some user will request some
 * platform-specific feature (such as sending files to the recycle bin, instead
 * of erasing it from the filesystem), and this need will not be filled by your
 * portable library.  Because most portable libraries try to completely hide the
 * underlying platform-specific resources, you will be in a pinch.
 *
 * @subsection portable-facade Building on the shoulders of giants
 *
 * Of course, if platform specific code is easier to write, building a platform
 * agnostic library is easier to write too: you can write a facade to services
 * offered by all platforms by using high-level platform-specifc libraries.
 * Then, this library can concentrate on providing the best possible interface,
 * rather than fighting with all the low-level APIs.  In such a library, the
 * code would express only what is of true interest: the differences between the
 * platform at a conceptual level (i.e. where capabilities differ).
 *
 * If this library offers a clean way to switch from the portable facade to
 * equivalently high-level non-portable counterparts, you would be able to keep
 * your increased productivity by using a high-level portable library and still
 * fill the gaps when your users request a non-portable feature.
 *
 *
 * @section yet-another-w32-api Yet another C++ API for Win32?
 *
 * Yes.  MFC is old, it stinks and it's hard to use.  Since its development, C++
 * best practices have evolved enormously.  C++ developers for Windows need a
 * cleaner, more modern abstraction and better documentation.  Hopefully, this
 * library will fill that gap.
 *
 * Where possible, this library tries to avoid locking you in.  Most kernel
 * objects (threads, mutexes, etc.) allow you to wrap handles allocated directly
 * using the Win32 API or with another library (MFC) and expose the handle, such
 * that you can convert to and from legacy code where possible.
 */
