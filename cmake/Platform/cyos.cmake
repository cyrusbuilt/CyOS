# This is a quick compiler definition for z88dk

set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS FALSE)
set(CMAKE_C_OUTPUT_EXTENSION .o)

# To help the find_xxx() commands
set(CMAKE_SYSTEM_INCLUDE_PATH $ENV{Z88DK_HOME}/include)
set(CMAKE_SYSTEM_LIBRARY_PATH $ENV{Z88DK_HOME}/lib)
set(CMAKE_SYSTEM_PROGRAM_PATH $ENV{Z88DK_HOME}/bin)
