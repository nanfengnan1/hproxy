cmake_minimum_required(VERSION 3.0.0)

project(hproxy C)

##############################################################################
# check os and hardware artichecture 
##############################################################################
message(STATUS "Configuring on/for: ${CMAKE_SYSTEM_NAME}")
message(STATUS "processor artichecture: ${CMAKE_SYSTEM_PROCESSOR}")

##############################################################################
# set c11 standard and build settings
##############################################################################
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# CMAKE_BUILD_TYPE: Debug, Release, RelWithDebInfo, MinSizeRel
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Werror")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Configuring on/for Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "Configuring on/for macOS")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Configuring on/for Windows")
elseif(CMAKE_SYSTEM_NAME STREQUAL "AIX")
    message(STATUS "Configuring on/for IBM AIX")
else()
    message(STATUS "Configuring on/for ${CMAKE_SYSTEM_NAME}")
endif()

##############################################################################
# set application name, version and write to config.h
##############################################################################
set(APPLICATION_NAME ${PROJECT_NAME})

set(APPLICATION_VERSION_MAJOR "1")
set(APPLICATION_VERSION_MINOR "0")
set(APPLICATION_VERSION_PATCH "0")

set(APPLICATION_VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}.${APPLICATION_VERSION_PATCH}")

message(STATUS "application_version: ${APPLICATION_VERSION}")

##############################################################################
# add global variable and write to config.h
##############################################################################
set(PACKAGE ${APPLICATION_NAME})
set(VERSION ${APPLICATION_VERSION})
set(DATADIR ${DATA_INSTALL_DIR})
set(LIBDIR ${LIB_INSTALL_DIR})
set(PLUGINDIR "${PLUGIN_INSTALL_DIR}-${LIBRARY_SOVERSION}")
set(SYSCONFDIR ${SYSCONF_INSTALL_DIR})
set(BINARYDIR ${CMAKE_BINARY_DIR})
set(SOURCEDIR ${CMAKE_SOURCE_DIR})

##############################################################################
# add global variable
##############################################################################
set(HPROXY_DESCRIPTION "hproxy is a proxy for redis and toolkit written (and providing API) in C.")

##############################################################################
# headers, structs and functions check and write to config.
# related command define in cmake.modules in document
# import cmake module and check operation
##############################################################################
# import related cmake modules
include(CheckIncludeFile)
include(CheckSymbolExists)
include(CheckFunctionExists)
include(CheckLibraryExists)
include(CheckTypeSize)
include(CheckCXXSourceCompiles)
include(CheckStructHasMember)
include(CheckCompilerFlag)

# check HEADER FILES
check_include_file(assert.h HAVE_ASSERT_H)
check_include_file(time.h HAVE_TIME_H)
check_include_file(pthread.h HAVE_PTHREAD_H)
check_Include_file(hiredis/hiredis.h HAVE_HIREDIS_H)
check_include_file(uv.h HAVE_UV_H)
check_include_file(stdatomic.h HAVE_STDATOMIC_H)

# check STRUCTS
check_struct_has_member("struct timespec" tv_sec "time.h" HAVE_STRUCT_TIMESPEC)

# check FUNCTIONS
check_function_exists(calloc HAVE_CALLOC)

check_compiler_flag(C "-march=native" _march_native_works)

##############################################################################
# find packages and include header
##############################################################################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
message(STATUS "CMAKE_ROOT: ${CMAKE_ROOT}")

# find Pcre2 library
find_package(Pcre2 10.34 REQUIRED)
include_directories(${PCRE2_INCLUDE_DIRS})

# find Hiredis library
find_package(Hiredis 1.2.0 REQUIRED)
include_directories(${HIREDIS_INCLUDE_DIRS})

# find Libuv library
find_package(Libuv 1.5.0 REQUIRED)
include_directories(${LIBUV_INCLUDE_DIRS})

# find Pthread library
find_package(Threads REQUIRED)
include_directories(${THREAD_INCLUDE_DIR})

# find cmocka for utest
find_package(Cmocka 1.0.1 REQUIRED)
include_directories(${CMOCKA_INCLUDE_DIR})

##############################################################################
# import custom Modules
##############################################################################
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(GenDoc)
include(GenCoverage)

##############################################################################
# add subdirectory
##############################################################################
add_subdirectory(src)

##############################################################################
# generate config.h from config.h.in
##############################################################################
configure_file(config.h.in config.h)

##############################################################################
# enable cross compile
##############################################################################
option(CROSS_COMPILE "hproxy support to cross compile" OFF)
if (CROSS_COMPILE)
	
endif (CROSS_COMPILE)

##############################################################################
# enable tests
##############################################################################
option(ENABLE_UTEST  "enable unit test" ON)
if (ENABLE_UTEST)
	enable_testing()
    add_subdirectory(tests)
endif (ENABLE_UTEST)

##############################################################################
# enable coverage report
##############################################################################
option(ENABLE_COVERAGE "Build code coverage report from tests" OFF)
if (ENABLE_COVERAGE)
    gen_coverage_enable(${UNIT_TESTING})
endif (ENABLE_COVERAGE)

# create coverage target for generating coverage reports
gen_coverage("utest_.*" "utest_.*_valgrind")

##############################################################################
# enable doxygen doc
##############################################################################
option(ENABLE_DOC "Build source code document" ON)
option(ENABLE_TEST_DOXYGEN "build test doxygen doc" OFF)
if (ENABLE_DOC)
	set(project_logo ${CMAKE_SOURCE_DIR}/doc/logo.png)

	set(doxy_files
		${CMAKE_SOURCE_DIR}/doc/build.dox
		${PROJECT_BINARY_DIR}/config.h
    	${CMAKE_SOURCE_DIR}/src)

    if (ENABLE_UTEST)
		set(doxy_files
			${CMAKE_SOURCE_DIR}/doc/build.dox
			${PROJECT_BINARY_DIR}/config.h
	    	${CMAKE_SOURCE_DIR}/src
	    	${CMAKE_SOURCE_DIR}/tests)
	else (ENABLE_UTEST)
		set(doxy_files
			${CMAKE_SOURCE_DIR}/doc/build.dox
			${PROJECT_BINARY_DIR}/config.h
	    	${CMAKE_SOURCE_DIR}/src)		
    endif (ENABLE_UTEST)

	build_doxygen("${doxy_files}" ${APPLICATION_VERSION} ${HPROXY_DESCRIPTION} ${project_logo})
endif()

##############################################################################
# enable sphinx doc, waiting to support
##############################################################################

##############################################################################
# install and uninstall
##############################################################################
include(GNUInstallDirs)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR} CACHE PATH "Installation directory for libraries")
set(INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR} CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR} CACHE PATH "Installation directory for header files")
set(INSTALL_CMAKEDIR ${DEF_INSTALL_CMAKEDIR} CACHE PATH "Installation directory for CMake files")

install(
  TARGETS
	hiproxy
	hproxy
  ARCHIVE
    DESTINATION ${INSTALL_LIBDIR}
    COMPONENT lib
  RUNTIME
    DESTINATION ${INSTALL_BINDIR}
    COMPONENT bin
  LIBRARY
    DESTINATION ${INSTALL_LIBDIR}
    COMPONENT lib
  PUBLIC_HEADER
    DESTINATION ${INSTALL_INCLUDEDIR}/message
    COMPONENT dev
  )

##############################################################################
# enable show finnal configurations
##############################################################################
option(HPROXY_SHOW_REPORT "Show the final configuration report" ON)
if (HPROXY_SHOW_REPORT)
STRING(TOUPPER "${CMAKE_BUILD_TYPE}" buildtype)
  if (CMAKE_C_FLAGS)
    SET(cfsp " ")
  endif(CMAKE_C_FLAGS)
  message(STATUS "")
  message(STATUS "")
  message(STATUS "HPROXY configuration summary:")
  message(STATUS "")
  message(STATUS "  Install prefix .................. : ${CMAKE_INSTALL_PREFIX}")
  message(STATUS "  C compiler ...................... : ${CMAKE_C_COMPILER}")
  message(STATUS "  C compiler flags ................ : ${CMAKE_C_FLAGS}${cfsp}${CMAKE_C_FLAGS_${buildtype}}")
  message(STATUS "  C program flags ................. : ${CMAKE_EXE_LINKER_FLAGS}")
  message(STATUS "")
  
  if (PCRE2_FOUND)
    message(STATUS "  Link hproxy with libpcre2 ..... : ${PCRE2_LIBRARY}")
  else (PCRE2_FOUND)
    message(STATUS "  Link hproxy with libpcre2 ..... : Library not found" )
  endif (PCRE2_FOUND)

  if (HIREDIS_FOUND)
    message(STATUS "  Link hproxy with libphiredis .. : ${HIREDIS_LIBRARY}")
  else (HIREDIS_FOUND)
    message(STATUS "  Link hproxy with libphiredis .. : Library not found" )
  endif (HIREDIS_FOUND)  

  if (LIBUV_FOUND)
    message(STATUS "  Link hproxy with libuv ........ : ${LIBUV_LIBRARY}")
  else (LIBUV_FOUND)
    message(STATUS "  Link hproxy with libuv ........ : Library not found" )
  endif (LIBUV_FOUND)

#  message(STATUS "install library path: ............. : ${CMAKE_INSTALL_PREFIX}/${INSTALL_LIB}"

  message(STATUS "")
endif (HPROXY_SHOW_REPORT)
