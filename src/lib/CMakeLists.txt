
##############################################################################
# hproxy shared library 
##############################################################################
add_library(hiproxy SHARED
	zlog.c
	regex.c
	hxy_hiredis.c)

# configure library property
set_target_properties(hiproxy PROPERTIES VERSION ${APPLICATION_VERSION} SOVERSION 0)
set(HIPROXY_LIBRARY hiproxy)

##############################################################################
# link third_party library 
##############################################################################
target_link_libraries(hiproxy PUBLIC ${PCRE2_LIBRARY} ${HIREDIS_LIBRARY} ${LIBUV_LIBRARY})

message(STATUS "lib project_source_dir: ${PROJECT_SOURCE_DIR}, ${PROJECT_SOURCE_DIR}/src/lib")    
