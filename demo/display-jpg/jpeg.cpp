// (( Andre Louis Caron <andre.louis.caron@usherbrooke.ca> ))

#include "jpeg.hpp"

namespace {

    // When libjpeg doesn't link with the same runtime, calling ::fread(),
    // ::fwrite() and ::fflush() manually is required in order to use the
    // FILE* I/O routines as the code who allocates the FILE* structure.

}

namespace jpeg {}

    // Try to link automagically!
#ifdef _MSC_VER
#   pragma comment ( lib, "jpeg.lib" )
#endif
