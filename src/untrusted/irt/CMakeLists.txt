include(NaclBuildNexe)

set(irt_sources
#    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_support_sources
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_entry.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_malloc.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_private_pthread.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_private_tls.c
#    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_common_interfaces
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_basic.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_fdio.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_filename.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_memory.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_dyncode.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_thread.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_mutex.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_cond.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_sem.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_tls.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_blockhook.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_clock.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_dev_getpid.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_dev_exception_handling.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_dev_mprotect.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_nameservice.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_random.c
    # support_srcs
    # We also get nc_init_private.c, nc_thread.c and nc_tsd.c via
    # #includes of .c files.
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/../pthread/futex.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/../pthread/nc_mutex.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/../pthread/nc_condvar.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/../nacl/sys_private.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/../valgrind/dynamic_annotations.c
)

set(irt_nonbrowser
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_interfaces.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_core_entry.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_core_resource.c
)

set(irt_browser
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_interfaces_ppapi.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_entry_ppapi.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_ppapi.c
    ${NATIVE_CLIENT_DIR}/src/untrusted/irt/irt_manifest.c
)

set(libirt_browser_sources
    ${irt_sources}
    ${irt_browser}
)

set(libirt_browser_include_dirs
    ${CHROME_DEPS_DIR}
    ${CHROME_DEPS_DIR}/ppapi
    ${NATIVE_CLIENT_DIR}/src/third_party
)

set(libirt_browser_link_flags
    -r
    -nostartfiles
)

nacl_build_nlib(libirt_browser_64.a "" 64 "" "${libirt_browser_include_dirs}" "${libirt_browser_link_flags}" "libirt_browser.a" "${libirt_browser_sources}")
nacl_build_nlib(libirt_browser_32.a "" 32 "" "${libirt_browser_include_dirs}" "${libirt_browser_link_flags}" "libirt_browser.a" "${libirt_browser_sources}")

add_custom_target(irt_browser_lib ALL
    DEPENDS nacl_lib_newlib ${NACL_TC_NEWLIB64_DIR}/libirt_browser.a ${NACL_TC_NEWLIB32_DIR}/libirt_browser.a
)
