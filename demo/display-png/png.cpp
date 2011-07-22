// (( Andre Louis Caron <andre.louis.caron@usherbrooke.ca> ))

#include "png.hpp"

namespace {

    // When libpng doesn't link with the same runtime, calling ::fread(),
    // ::fwrite() and ::fflush() manually is required in order to use the
    // FILE* I/O routines as the code who allocates the FILE* structure.

}

namespace png {}

    // Try to link automagically!
#ifdef _MSC_VER
#   pragma comment ( lib, "libpng.lib" )
#   pragma comment ( lib, "zlib.lib" )
#endif
