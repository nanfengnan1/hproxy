# - Try to find CMocka
# Once done this will define
#
#  CMOCKA_ROOT_DIR - Set this variable to the root installation of CMocka
#
# Read-Only variables:
#  CMOCKA_FOUND - system has CMocka
#  CMOCKA_INCLUDE_DIR - the CMocka include directory
#  CMOCKA_LIBRARIES - Link these to use CMocka
#  CMOCKA_DEFINITIONS - Compiler switches required for using CMocka
#
#=============================================================================
#  Copyright (c) 2011-2012 Andreas Schneider <asn@cryptomilk.org>
#
#  Distributed under the OSI-approved BSD License (the "License");
#  see accompanying file Copyright.txt for details.
#
#  This software is distributed WITHOUT ANY WARRANTY; without even the
#  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#  See the License for more information.
#=============================================================================
#

find_path(CMOCKA_INCLUDE_DIR
    NAMES
        cmocka.h
    PATHS
        ${CMOCKA_ROOT_DIR}/include
)

find_library(CMOCKA_LIBRARY
    NAMES
        cmocka
    PATHS
        ${CMOCKA_ROOT_DIR}/include
)

if (CMOCKA_LIBRARY)
  set(CMOCKA_LIBRARIES
      ${CMOCKA_LIBRARIES}
      ${CMOCKA_LIBRARY}
  )
endif (CMOCKA_LIBRARY)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Cmocka DEFAULT_MSG CMOCKA_LIBRARIES CMOCKA_INCLUDE_DIR)

# show the CMOCKA_INCLUDE_DIR and CMOCKA_LIBRARIES variables only in the advanced view
mark_as_advanced(CMOCKA_INCLUDE_DIR CMOCKA_LIBRARIES)

