#ifndef _w32_hpp__
#define _w32_hpp__

// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "__configure__.hpp"

namespace w32 {}

/*!
 * @defgroup w32 Core services.
 *
 * This group contains very basic services (e.g. string manipulation) or
 * services that have not been categorized into a particular category.
 */

#include <w32/Architecture.hpp>
#include <w32/astring.hpp>
#include <w32/bstring.hpp>
#include <w32/CodePage.hpp>
#include <w32/computername.hpp>
#include <w32/currentdirectory.hpp>
#include <w32/Console.hpp>
#include <w32/Environment.hpp>
#include <w32/Delta.hpp>
#include <w32/Error.hpp>
#include <w32/Module.hpp>
#include <w32/mstring.hpp>
#include <w32/Object.hpp>
#include <w32/Resource.hpp>
#include <w32/string.hpp>
#include <w32/strings.hpp>
#include <w32/System.hpp>
#include <w32/Time.hpp>
#include <w32/Timespan.hpp>
#include <w32/types.hpp>
#include <w32/Version.hpp>
#include <w32/Waitable.hpp>
#include <w32/Variant.hpp>

#endif /* _w32_hpp__ */
