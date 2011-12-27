#ifndef _w32_io_hpp__
#define _w32_io_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 {
    namespace io {}
}

#include <w32.io/AnonymousPipe.hpp>
#include <w32.io/Channel.hpp>
#include <w32.io/CompletionPort.hpp>
#include <w32.io/ConsoleInput.hpp>
#include <w32.io/ConsoleOutput.hpp>
#include <w32.io/InputFile.hpp>
#include <w32.io/InputStream.hpp>
#include <w32.io/NamedPipe.hpp>
#include <w32.io/Null.hpp>
#include <w32.io/OutputFile.hpp>
#include <w32.io/OutputStream.hpp>
#include <w32.io/SerialPort.hpp>
#include <w32.io/StandardError.hpp>
#include <w32.io/StandardInput.hpp>
#include <w32.io/StandardOutput.hpp>
#include <w32.io/Stream.hpp>
#include <w32.io/streambuf.hpp>
#include <w32.io/Transfer.hpp>

#endif /* _w32_io_hpp__ */
