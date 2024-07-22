# - Find THREAD
# Find the native THREAD headers and libraries.
#
# THREAD_INCLUDE_DIRS    - where to find pthread.h, etc.
# THREAD_LIBRARIES       - List of libraries when using thread.
# THREADS_FOUND          - True if thread found.
include(FindPackageHandleStandardArgs)

if(THREAD_LIBRARY AND THREAD_INCLUDE_DIR)
    # in cache already
    set(THREADS_FOUND TRUE)
else()
    find_path(THREAD_INCLUDE_DIR
        NAMES
        pthread.h
        PATHS
        /usr/include
        /usr/local/include
        /opt/local/include
        ${CMAKE_INCLUDE_PATH}
        ${CMAKE_INSTALL_PREFIX}/include)

    find_library(THREAD_LIBRARY
        NAMES
        pthread
        PATHS
        /usr/lib
        /usr/lib64
        /usr/local/lib
        /usr/local/lib64
        /opt/local/lib
        ${CMAKE_LIBRARY_PATH}
        ${CMAKE_INSTALL_PREFIX}/lib)

    set(THREAD_INCLUDE_DIRS ${THREAD_INCLUDE_DIR})
    set(THREAD_LIBRARIES ${THREAD_LIBRARY})
    mark_as_advanced(THREAD_INCLUDE_DIRS THREAD_LIBRARIES)

    find_package_handle_standard_args(Threads FOUND_VAR THREADS_FOUND
        REQUIRED_VARS THREAD_LIBRARY THREAD_INCLUDE_DIR)
endif()