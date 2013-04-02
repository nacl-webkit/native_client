include(NaclBuildNexe)

set(sources_for_standard_interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/clock.c
    ${CMAKE_CURRENT_SOURCE_DIR}/clock_getres.c
    ${CMAKE_CURRENT_SOURCE_DIR}/clock_gettime.c
    ${CMAKE_CURRENT_SOURCE_DIR}/close.c
    ${CMAKE_CURRENT_SOURCE_DIR}/dup.c
    ${CMAKE_CURRENT_SOURCE_DIR}/_exit.c
    ${CMAKE_CURRENT_SOURCE_DIR}/fstat.c
    ${CMAKE_CURRENT_SOURCE_DIR}/getdents.c
    ${CMAKE_CURRENT_SOURCE_DIR}/getpid.c
    ${CMAKE_CURRENT_SOURCE_DIR}/gettimeofday.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lock.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lseek.c
    ${CMAKE_CURRENT_SOURCE_DIR}/malloc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/mmap.c
    ${CMAKE_CURRENT_SOURCE_DIR}/munmap.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nanosleep.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_interface_query.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_read_tp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/open.c
    ${CMAKE_CURRENT_SOURCE_DIR}/read.c
    ${CMAKE_CURRENT_SOURCE_DIR}/pthread_initialize_minimal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/pthread_stubs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/sbrk.c
    ${CMAKE_CURRENT_SOURCE_DIR}/sched_yield.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stacktrace.c
    ${CMAKE_CURRENT_SOURCE_DIR}/start.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stat.c
    ${CMAKE_CURRENT_SOURCE_DIR}/sysconf.c
    ${CMAKE_CURRENT_SOURCE_DIR}/tls.c
    ${CMAKE_CURRENT_SOURCE_DIR}/write.c
)

set(sources_for_nacl_extensions
    ${CMAKE_CURRENT_SOURCE_DIR}/gc_hooks.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_irt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_tls_get.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_tls_init.c
)

set(sources_for_imc_syscalls
   ${CMAKE_CURRENT_SOURCE_DIR}/imc_accept.c
   ${CMAKE_CURRENT_SOURCE_DIR}/imc_connect.c
   ${CMAKE_CURRENT_SOURCE_DIR}/imc_makeboundsock.c
   ${CMAKE_CURRENT_SOURCE_DIR}/imc_mem_obj_create.c
   ${CMAKE_CURRENT_SOURCE_DIR}/imc_recvmsg.c
   ${CMAKE_CURRENT_SOURCE_DIR}/imc_sendmsg.c
   ${CMAKE_CURRENT_SOURCE_DIR}/imc_socketpair.c
   ${CMAKE_CURRENT_SOURCE_DIR}/nameservice.c
)

set(nacl_lib_newlib_sources
    ${sources_for_nacl_extensions}
    ${sources_for_standard_interfaces}
)

set(nacl_lib_newlib_include_dirs
    ${CHROME_DEPS_DIR}
    ${CHROME_DEPS_DIR}/ppapi
    ${NATIVE_CLIENT_DIR}/src/third_party
)

nacl_build_nlib(nacl_lib_newlib_64.a "" 64 "" "${nacl_lib_newlib_include_dirs}" "" "" "libnacl.a" "${nacl_lib_newlib_sources}")
nacl_build_nlib(nacl_lib_newlib_32.a "" 32 "" "${nacl_lib_newlib_include_dirs}" "" "" "libnacl.a" "${nacl_lib_newlib_sources}")

add_custom_target(nacl_lib_newlib ALL
    DEPENDS build_nacl_lib_newlib_64.a build_nacl_lib_newlib_32.a
)

nacl_build_nlib(libimc_syscalls_64.a "" 64 "" "${nacl_lib_newlib_include_dirs}" "" "" "libimc_syscalls.a" "${sources_for_imc_syscalls}")
nacl_build_nlib(libimc_syscalls_32.a "" 32 "" "${nacl_lib_newlib_include_dirs}" "" "" "libimc_syscalls.a" "${sources_for_imc_syscalls}")

add_custom_target(imc_syscalls_lib ALL
    DEPENDS build_libimc_syscalls_64.a build_libimc_syscalls_32.a
)

