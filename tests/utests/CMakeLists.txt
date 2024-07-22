include_directories(${CMAKE_CURRENT_SOURCE_DIR})

hy_add_utest(NAME cmocka SOURCES test_cmocka.c)
hy_add_utest(NAME atomic SOURCES test_atomic.c)
hy_add_utest(NAME regex SOURCES test_regex.c)
hy_add_utest(NAME kopt SOURCES test_kopt.c)
hy_add_utest(NAME snprintf SOURCES test_snprintf.c)
hy_add_utest(NAME hiredis SOURCES test_hiredis.c)
