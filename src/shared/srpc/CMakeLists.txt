set(NACL_SHARED_NONNACL_SPRC_LIBRARY_NAME nonnacl_srpc)
set(NACL_SHARED_NONNACL_SPRC_LIBRARY_SOURCES
    ${NATIVE_CLIENT_DIR}/src/shared/srpc/invoke.c
    ${NATIVE_CLIENT_DIR}/src/shared/srpc/module_init_fini.c
    ${NATIVE_CLIENT_DIR}/src/shared/srpc/nacl_srpc.c
    ${NATIVE_CLIENT_DIR}/src/shared/srpc/nacl_srpc_message.c
    ${NATIVE_CLIENT_DIR}/src/shared/srpc/rpc_log.c
    ${NATIVE_CLIENT_DIR}/src/shared/srpc/rpc_serialize.c
    ${NATIVE_CLIENT_DIR}/src/shared/srpc/rpc_service.c
    ${NATIVE_CLIENT_DIR}/src/shared/srpc/rpc_server_loop.c
)

set(NACL_SHARED_NONNACL_SPRC_INCLUDE_DIRECTORIES
    ${NATIVE_CLIENT_DIR}/..
    ${NATIVE_CLIENT_DIR}/src/third_party
    ${NATIVE_CLIENT_DIR}/src/shared/srpc
)
    
add_definitions(-fPIC)

include_directories(${NACL_SHARED_NONNACL_SPRC_INCLUDE_DIRECTORIES})
add_library(${NACL_SHARED_NONNACL_SPRC_LIBRARY_NAME} STATIC ${NACL_SHARED_NONNACL_SPRC_LIBRARY_SOURCES})

# untrusted part
include(NaclBuildNexe)

set(libsrpc_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/invoke.c
    ${CMAKE_CURRENT_SOURCE_DIR}/module_init_fini.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_srpc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_srpc_message.c
    ${CMAKE_CURRENT_SOURCE_DIR}/rpc_log.c
    ${CMAKE_CURRENT_SOURCE_DIR}/rpc_serialize.c
    ${CMAKE_CURRENT_SOURCE_DIR}/rpc_service.c
    ${CMAKE_CURRENT_SOURCE_DIR}/rpc_server_loop.c
    ${CMAKE_CURRENT_SOURCE_DIR}/accept.c
    ${CMAKE_CURRENT_SOURCE_DIR}/accept_threaded.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_srpc_ppapi_plugin_init.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_srpc_ppapi_plugin_internal.c
)

set(libsrpc_include_dirs
    ${CHROME_DEPS_DIR}
    ${CHROME_DEPS_DIR}/ppapi
    ${NATIVE_CLIENT_DIR}/src/third_party
)

nacl_build_nlib(libsrpc_64.a "" 64 "" "${libsrpc_include_dirs}" "" "libsrpc.a" "${libsrpc_sources}")
nacl_build_nlib(libsrpc_32.a "" 32 "" "${libsrpc_include_dirs}" "" "libsrpc.a" "${libsrpc_sources}")

add_custom_target(srpc_lib ALL
    DEPENDS ${NACL_TC_NEWLIB64_DIR}/libsrpc.a ${NACL_TC_NEWLIB32_DIR}/libsrpc.a
)
