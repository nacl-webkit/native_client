set(NACL_SHARED_PLATFORM_LIBRARY_NAME nacl_shared_platform)
set(NACL_SHARED_PLATFORM_LIBRARY_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_check.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_global_secure_random.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_host_desc_common.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_interruptible_condvar.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_interruptible_mutex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_log.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_secure_random_common.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_sync_checked.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_time_common.c
    ${CMAKE_CURRENT_SOURCE_DIR}/platform_init.c
    ${CMAKE_CURRENT_SOURCE_DIR}/refcount_base.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/linux/nacl_clock.c
    ${CMAKE_CURRENT_SOURCE_DIR}/linux/nacl_host_dir.c
    ${CMAKE_CURRENT_SOURCE_DIR}/linux/nacl_semaphore.c
    ${CMAKE_CURRENT_SOURCE_DIR}/posix/aligned_malloc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/posix/condition_variable.c
    ${CMAKE_CURRENT_SOURCE_DIR}/posix/lock.c
    ${CMAKE_CURRENT_SOURCE_DIR}/posix/nacl_exit.c
    ${CMAKE_CURRENT_SOURCE_DIR}/posix/nacl_fast_mutex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/posix/nacl_find_addrsp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/posix/nacl_host_desc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/posix/nacl_host_desc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/posix/nacl_secure_random.c
    ${CMAKE_CURRENT_SOURCE_DIR}/posix/nacl_thread_id.c
    ${CMAKE_CURRENT_SOURCE_DIR}/posix/nacl_threads.c
    ${CMAKE_CURRENT_SOURCE_DIR}/posix/nacl_time.c
    ${CMAKE_CURRENT_SOURCE_DIR}/posix/nacl_timestamp.c
)

set(NACL_SHARED_PLATFORM_INCLUDE_DIRECTORIES
    ${NATIVE_CLIENT_DIR}/..
    ${NATIVE_CLIENT_DIR}/src/third_party
    ${CMAKE_CURRENT_SOURCE_DIR}
)
    
add_definitions(-fPIC)

include_directories(${NACL_SHARED_PLATFORM_INCLUDE_DIRECTORIES})
add_library(${NACL_SHARED_PLATFORM_LIBRARY_NAME} STATIC ${NACL_SHARED_PLATFORM_LIBRARY_SOURCES})

# untrusted part
include(NaclBuildNexe)

set(libplatform_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_check.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_log.c
    ${CMAKE_CURRENT_SOURCE_DIR}/posix/condition_variable.c
    ${CMAKE_CURRENT_SOURCE_DIR}/posix/lock.c
    ${CMAKE_CURRENT_SOURCE_DIR}/posix/nacl_exit.c
    ${CMAKE_CURRENT_SOURCE_DIR}/posix/nacl_thread_id.c
    ${CMAKE_CURRENT_SOURCE_DIR}/posix/nacl_threads.c
    ${CMAKE_CURRENT_SOURCE_DIR}/posix/nacl_timestamp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_sync_checked.c
    ${CMAKE_CURRENT_SOURCE_DIR}/refcount_base.cc
)

set(libplatform_include_dirs
    ${CHROME_DEPS_DIR}
    ${CHROME_DEPS_DIR}/ppapi
    ${NATIVE_CLIENT_DIR}/src/third_party
)

nacl_build_nlib(libplatform_64.a "" 64 "" "${libplatform_include_dirs}" "" "" "libplatform.a" "${libplatform_sources}")
nacl_build_nlib(libplatform_32.a "" 32 "" "${libplatform_include_dirs}" "" "" "libplatform.a" "${libplatform_sources}")

add_custom_target(platform_lib ALL
    DEPENDS build_libplatform_64.a build_libplatform_32.a
)
