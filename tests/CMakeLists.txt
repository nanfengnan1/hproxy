# Correct RPATH usage on OS X
set(CMAKE_MACOSX_RPATH TRUE)

include_directories(SYSTEM ${HPROXY_INCLUDE_DIR})
include_directories(${PROJECT_BINARY_DIR}/tests/)
include_directories(${PROJECT_SOURCE_DIR}/src/lib)

# Define a function to add unit tests
function(hy_add_utest)
    cmake_parse_arguments(ADDTEST "" "NAME;WRAP" "SOURCES" ${ARGN})
    set(TEST_NAME utest_${ADDTEST_NAME})

    # Prepare the list of source files
    foreach(TEST_SOURCE ${ADDTEST_SOURCES})
        list(APPEND TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_SOURCE})
    endforeach()

    # Set the test name
    set(TEST_TARGET ${TEST_NAME})

    # Add the executable for the test
    add_executable(${TEST_TARGET} ${TEST_SOURCES})

	target_link_libraries(${TEST_TARGET} ${CMOCKA_LIBRARIES} hiproxy ${THREAD_LIBRARY})

	message(STATUS "****** ${PROJECT_SOURCE_DIR} ******")

    # Add test to CTest
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_TARGET})

    # Optionally, you can set properties or environment variables for the test
    # For example:
    # set_property(TEST ${TEST_NAME} PROPERTY LABELS "unit")

    # Set output directory for the test executable
    set_target_properties(${TEST_TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests")
endfunction()

if(ENABLE_UTEST)
    add_subdirectory(utests)
endif()