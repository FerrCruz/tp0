# Libraries
LIBS=commons pthread readline m

# Custom libraries' paths
SHARED_LIBPATHS=
STATIC_LIBPATHS=


# Compiler flags
CDEBUG=-g -Wall -DDEBUG -fdiagnostics-color=always -Werror
CRELEASE=-O3 -Wall -DNDEBUG -fcommon -Werror