set(NACL_SHARED_GIO_LIBRARY_NAME nacl_shared_gio)
set(NACL_SHARED_GIO_LIBRARY_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/
)
set(common_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/gio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/gio_mem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/gprintf.c
    ${CMAKE_CURRENT_SOURCE_DIR}/gio_mem_snapshot.c
)

set(trusted_sources
    ${common_sources}
    ${CMAKE_CURRENT_SOURCE_DIR}/gio_pio.c
)

set(NACL_SHARED_GIO_INCLUDE_DIRECTORIES
    ${NATIVE_CLIENT_DIR}/..
    ${NATIVE_CLIENT_DIR}/src/third_party
    ${CMAKE_CURRENT_SOURCE_DIR}
)
    
add_definitions(-fPIC)

include_directories(${NACL_SHARED_GIO_INCLUDE_DIRECTORIES})
add_library(${NACL_SHARED_GIO_LIBRARY_NAME} STATIC ${trusted_sources})

# untrusted part
include(NaclBuildNexe)

set(libgio_include_dirs
    ${CHROME_DEPS_DIR}
    ${CHROME_DEPS_DIR}/ppapi
    ${NATIVE_CLIENT_DIR}/src/third_party
)

nacl_build_nlib(libgio_64.a "" 64 "" "${libgio_include_dirs}" "" "" "libgio.a" "${common_sources}")
nacl_build_nlib(libgio_32.a "" 32 "" "${libgio_include_dirs}" "" "" "libgio.a" "${common_sources}")

add_custom_target(gio_lib ALL
    DEPENDS build_libgio_64.a build_libgio_32.a
)
