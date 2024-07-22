# - Find Hiredis
# Find the native Hiredis headers and libraries.

include(FindPackageHandleStandardArgs)

if(HIREDIS_LIBRARIES AND HIREDIS_INCLUDE_DIRS)
    # Hiredis variables are already in cache
    set(HIREDIS_FOUND TRUE)
else()
    find_path(HIREDIS_INCLUDE_DIR
        NAMES
        hiredis/hiredis.h
        PATHS
        /usr/include
        /usr/local/include
        /opt/local/include
        /sw/include
        ${CMAKE_INCLUDE_PATH}
        ${CMAKE_INSTALL_PREFIX}/include)

    find_library(HIREDIS_LIBRARY
        NAMES
        hiredis
        PATHS
        /usr/lib
        /usr/lib64
        /usr/local/lib
        /usr/local/lib64
        /opt/local/lib
        /sw/lib
        ${CMAKE_LIBRARY_PATH}
        ${CMAKE_INSTALL_PREFIX}/lib)

    if(HIREDIS_INCLUDE_DIR AND HIREDIS_LIBRARY)
        set(HIREDIS_FOUND TRUE)
    endif()

    # Handle the QUIETLY and REQUIRED arguments and set HIREDIS_FOUND to TRUE if all listed variables are TRUE.
    find_package_handle_standard_args(Hiredis FOUND_VAR HIREDIS_FOUND
        REQUIRED_VARS HIREDIS_LIBRARY HIREDIS_INCLUDE_DIR)
endif()

# Export the variables
if(HIREDIS_FOUND)
    set(HIREDIS_LIBRARIES ${HIREDIS_LIBRARY})
    set(HIREDIS_INCLUDE_DIRS ${HIREDIS_INCLUDE_DIR})
    mark_as_advanced(HIREDIS_INCLUDE_DIRS HIREDIS_LIBRARIES)
endif()