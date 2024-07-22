##############################################################################
# search libuv and libhiredis packets, using pkgconfig, didn't cross platform
##############################################################################
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(LIBUV REQUIRED libuv)
# include_directories(${LIBUV_INCLUDE_DIRS})

# pkg_check_modules(LIBHIREDIS REQUIRED hiredis)
# include_directories(${LIBHIREDIS_INCLUDE_DIRS})
##############################################################################
# hproxy 
##############################################################################
add_executable(hproxy
	hproxy.c)

##############################################################################
# link dynamic library 
##############################################################################
target_link_libraries(hproxy PUBLIC hiproxy)

target_include_directories(hproxy PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/src/"
                          )
                          
target_link_libraries(hproxy PUBLIC
                      "${LIBUV_LIBRARIES}"
                      "${HIREDIS_LIBRARIES}"
                      )                          
                          
message(STATUS "project_source_dir: ${PROJECT_SOURCE_DIR}, ${PROJECT_BINARY_DIR}, ${PROJECT_LIBRARY_DIR}")                          