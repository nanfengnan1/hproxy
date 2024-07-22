# - Find libuv
# Find the native libuv headers and library.
#
# LIBUV_INCLUDE_DIRS   - where to find uv.h, etc.
# LIBUV_LIBRARIES      - List of libraries when using libuv.
# LIBUV_FOUND          - True if libuv found.
# LIBUV_VERSION        - The version of libuv found.

include(FindPackageHandleStandardArgs)

# Check if libuv has already been found
if(LIBUV_LIBRARIES AND LIBUV_INCLUDE_DIRS)
    set(LIBUV_FOUND TRUE)
else()
    # Search for the header file
    find_path(LIBUV_INCLUDE_DIR
        NAMES
        uv.h
        PATHS
        /usr/include
        /usr/local/include
        /opt/local/include
        ${CMAKE_INCLUDE_PATH}
        ${CMAKE_INSTALL_PREFIX}/include)

    # Search for the library
    find_library(LIBUV_LIBRARY
        NAMES
        uv
        PATHS
        /usr/lib
        /usr/lib64
        /usr/local/lib
        /usr/local/lib64
        /opt/local/lib
        ${CMAKE_LIBRARY_PATH}
        ${CMAKE_INSTALL_PREFIX}/lib)

    # Extract the version from the header if available
    if(LIBUV_INCLUDE_DIR AND EXISTS "${LIBUV_INCLUDE_DIR}/uv-version.h")
        file(STRINGS "${LIBUV_INCLUDE_DIR}/uv-version.h" LIBUV_VERSION_MAJOR
            REGEX "^#define[ \t]+UV_VERSION_MAJOR[ \t]+[0-9]+")
        string(REGEX REPLACE "^#define[ \t]+UV_VERSION_MAJOR[ \t]+([0-9]+)" "\\1" LIBUV_VERSION_MAJOR "${LIBUV_VERSION_MAJOR}")

        file(STRINGS "${LIBUV_INCLUDE_DIR}/uv-version.h" LIBUV_VERSION_MINOR
            REGEX "^#define[ \t]+UV_VERSION_MINOR[ \t]+[0-9]+")
        string(REGEX REPLACE "^#define[ \t]+UV_VERSION_MINOR[ \t]+([0-9]+)" "\\1" LIBUV_VERSION_MINOR "${LIBUV_VERSION_MINOR}")

        file(STRINGS "${LIBUV_INCLUDE_DIR}/uv-version.h" LIBUV_VERSION_PATCH
            REGEX "^#define[ \t]+UV_VERSION_PATCH[ \t]+[0-9]+")
        string(REGEX REPLACE "^#define[ \t]+UV_VERSION_PATCH[ \t]+([0-9]+)" "\\1" LIBUV_VERSION_PATCH "${LIBUV_VERSION_PATCH}")

        set(LIBUV_VERSION "${LIBUV_VERSION_MAJOR}.${LIBUV_VERSION_MINOR}.${LIBUV_VERSION_PATCH}")
    endif()

    # Set the output variables
    set(LIBUV_INCLUDE_DIRS ${LIBUV_INCLUDE_DIR})
    set(LIBUV_LIBRARIES ${LIBUV_LIBRARY})

    # Mark the advanced variables as hidden
    mark_as_advanced(LIBUV_INCLUDE_DIRS LIBUV_LIBRARIES)

    # Handle the QUIETLY and REQUIRED arguments and set LIBUV_FOUND to TRUE if all listed variables are TRUE.
    find_package_handle_standard_args(Libuv FOUND_VAR LIBUV_FOUND
        REQUIRED_VARS LIBUV_LIBRARY LIBUV_INCLUDE_DIR
        VERSION_VAR LIBUV_VERSION)
endif()