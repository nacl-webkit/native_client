CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(nacl_LIBRARY_NAME "nacl")
SET(nacl_LIBRARY_NAME ${nacl_LIBRARY_NAME} PARENT_SCOPE)
SET(nacl_SRC_DIR "${CMAKE_SOURCE_DIR}/Source/native_client/src")

SET(nacl_INCLUDE_DIRECTORIES "${nacl_SRC_DIR}/include/")
SET(nacl_INCLUDE_DIRECTORIES ${nacl_INCLUDE_DIRECTORIES} PARENT_SCOPE)

INCLUDE(${nacl_SRC_DIR}/../common.txt)

SET(nacl_SOURCES
    ${nacl_SRC_DIR}/shared/gio/gio.h
    ${nacl_SRC_DIR}/shared/gio/gio.c
    ${nacl_SRC_DIR}/shared/gio/gio_mem.c
    ${nacl_SRC_DIR}/shared/gio/gprintf.c
    ${nacl_SRC_DIR}/shared/gio/gio_mem_snapshot.c
    ${nacl_SRC_DIR}/shared/gio/gio_pio.c

    ${nacl_SRC_DIR}/shared/imc/nacl_imc_c.cc
    ${nacl_SRC_DIR}/shared/imc/nacl_imc_common.cc
    ${nacl_SRC_DIR}/shared/imc/nacl_imc.h
    ${nacl_SRC_DIR}/shared/imc/nacl_imc_c.h
    ${nacl_SRC_DIR}/shared/imc/linux/nacl_imc.cc
    ${nacl_SRC_DIR}/shared/imc/posix/nacl_imc_posix.cc

    ${nacl_SRC_DIR}/shared/platform/nacl_check.c
    ${nacl_SRC_DIR}/shared/platform/nacl_check.h
    ${nacl_SRC_DIR}/shared/platform/nacl_find_addrsp.h
    ${nacl_SRC_DIR}/shared/platform/nacl_global_secure_random.c
    ${nacl_SRC_DIR}/shared/platform/nacl_global_secure_random.h
    ${nacl_SRC_DIR}/shared/platform/nacl_host_dir.h
    ${nacl_SRC_DIR}/shared/platform/nacl_host_desc_common.c
    ${nacl_SRC_DIR}/shared/platform/nacl_host_desc.h
    ${nacl_SRC_DIR}/shared/platform/nacl_interruptible_condvar.c
    ${nacl_SRC_DIR}/shared/platform/nacl_interruptible_condvar.h
    ${nacl_SRC_DIR}/shared/platform/nacl_interruptible_mutex.c
    ${nacl_SRC_DIR}/shared/platform/nacl_interruptible_mutex.h
    ${nacl_SRC_DIR}/shared/platform/nacl_log.c
    ${nacl_SRC_DIR}/shared/platform/nacl_log.h
    ${nacl_SRC_DIR}/shared/platform/nacl_secure_random.h
    ${nacl_SRC_DIR}/shared/platform/nacl_secure_random_base.h
    ${nacl_SRC_DIR}/shared/platform/nacl_secure_random_common.c
    ${nacl_SRC_DIR}/shared/platform/nacl_semaphore.h
    ${nacl_SRC_DIR}/shared/platform/nacl_sync.h
    ${nacl_SRC_DIR}/shared/platform/nacl_sync_checked.c
    ${nacl_SRC_DIR}/shared/platform/nacl_sync_checked.h
    ${nacl_SRC_DIR}/shared/platform/nacl_threads.h
    ${nacl_SRC_DIR}/shared/platform/nacl_time.h
    ${nacl_SRC_DIR}/shared/platform/nacl_time_common.c
    ${nacl_SRC_DIR}/shared/platform/nacl_timestamp.h
    ${nacl_SRC_DIR}/shared/platform/platform_init.c
    ${nacl_SRC_DIR}/shared/platform/refcount_base.cc

    ${nacl_SRC_DIR}/shared/platform/posix/aligned_malloc.c
    ${nacl_SRC_DIR}/shared/platform/posix/condition_variable.c
    ${nacl_SRC_DIR}/shared/platform/posix/lock.c
    ${nacl_SRC_DIR}/shared/platform/posix/nacl_exit.c
    ${nacl_SRC_DIR}/shared/platform/posix/nacl_fast_mutex.c
    ${nacl_SRC_DIR}/shared/platform/posix/nacl_find_addrsp.c
    ${nacl_SRC_DIR}/shared/platform/posix/nacl_host_desc.c
    ${nacl_SRC_DIR}/shared/platform/posix/nacl_secure_random.c
    ${nacl_SRC_DIR}/shared/platform/posix/nacl_thread_id.c
    ${nacl_SRC_DIR}/shared/platform/posix/nacl_threads.c
    ${nacl_SRC_DIR}/shared/platform/posix/nacl_time.c
    ${nacl_SRC_DIR}/shared/platform/posix/nacl_timestamp.c
    ${nacl_SRC_DIR}/shared/platform/linux/nacl_clock.c
    ${nacl_SRC_DIR}/shared/platform/linux/nacl_host_dir.c
    ${nacl_SRC_DIR}/shared/platform/linux/nacl_semaphore.c

    ${nacl_SRC_DIR}/shared/srpc/invoke.c
    ${nacl_SRC_DIR}/shared/srpc/module_init_fini.c
    ${nacl_SRC_DIR}/shared/srpc/nacl_srpc.c
    ${nacl_SRC_DIR}/shared/srpc/nacl_srpc.h
    ${nacl_SRC_DIR}/shared/srpc/nacl_srpc_internal.h
    ${nacl_SRC_DIR}/shared/srpc/nacl_srpc_message.c
    ${nacl_SRC_DIR}/shared/srpc/rpc_log.c
    ${nacl_SRC_DIR}/shared/srpc/rpc_serialize.c
    ${nacl_SRC_DIR}/shared/srpc/rpc_service.c
    ${nacl_SRC_DIR}/shared/srpc/rpc_server_loop.c

    ${nacl_SRC_DIR}/trusted/debug_stub/abi.cc
    ${nacl_SRC_DIR}/trusted/debug_stub/debug_stub.cc
    ${nacl_SRC_DIR}/trusted/debug_stub/nacl_debug.cc
    ${nacl_SRC_DIR}/trusted/debug_stub/packet.cc
    ${nacl_SRC_DIR}/trusted/debug_stub/posix/debug_stub_posix.cc
    ${nacl_SRC_DIR}/trusted/debug_stub/posix/platform_impl.cc
    ${nacl_SRC_DIR}/trusted/debug_stub/posix/thread_impl.cc
    ${nacl_SRC_DIR}/trusted/debug_stub/session.cc
    ${nacl_SRC_DIR}/trusted/debug_stub/target.cc
    ${nacl_SRC_DIR}/trusted/debug_stub/thread_common.cc
    ${nacl_SRC_DIR}/trusted/debug_stub/transport_common.cc
    ${nacl_SRC_DIR}/trusted/debug_stub/util.cc

    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_base.c
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_base.h
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_cond.c
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_cond.h
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_custom.c
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_custom.h
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_dir.c
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_dir.h
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_effector.h
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_effector_trusted_mem.c
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_effector_trusted_mem.h
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_imc.c
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_imc.h
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_imc_shm.c
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_imc_shm.h
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_invalid.c
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_invalid.h
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_io.c
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_io.h
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_mutex.c
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_mutex.h
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_null.c
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_null.h
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_rng.c
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_rng.h
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_quota.c
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_quota.h
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_quota_interface.c
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_quota_interface.h
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_semaphore.c
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_semaphore.h
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_sync_socket.c
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_sync_socket.h
    ${nacl_SRC_DIR}/trusted/desc/nacl_desc_wrapper.cc
    ${nacl_SRC_DIR}/trusted/desc/nrd_all_modules.c
    ${nacl_SRC_DIR}/trusted/desc/nrd_all_modules.h
    ${nacl_SRC_DIR}/trusted/desc/nrd_xfer.c
    ${nacl_SRC_DIR}/trusted/desc/nrd_xfer.h
    ${nacl_SRC_DIR}/trusted/desc/nrd_xfer_intern.h
    ${nacl_SRC_DIR}/trusted/desc/linux/nacl_desc_sysv_shm.c
    ${nacl_SRC_DIR}/trusted/desc/linux/nacl_desc_sysv_shm.h
    ${nacl_SRC_DIR}/trusted/desc/posix/nacl_desc.c
    ${nacl_SRC_DIR}/trusted/desc/posix/nacl_desc_conn_cap.c
    ${nacl_SRC_DIR}/trusted/desc/posix/nacl_desc_imc_bound_desc.c
    ${nacl_SRC_DIR}/trusted/desc/posix/nacl_makeboundsock.c

    ${nacl_SRC_DIR}/trusted/interval_multiset/nacl_interval_range_tree.c
    ${nacl_SRC_DIR}/trusted/interval_multiset/nacl_interval_multiset_delete.c
    ${nacl_SRC_DIR}/trusted/interval_multiset/nacl_interval_list.c
    ${nacl_SRC_DIR}/trusted/interval_multiset/nacl_interval_multiset_factory.c

    ${nacl_SRC_DIR}/trusted/gio/gio_shm.h
    ${nacl_SRC_DIR}/trusted/gio/gio_shm.c
    ${nacl_SRC_DIR}/trusted/gio/gio_shm_unbounded.h
    ${nacl_SRC_DIR}/trusted/gio/gio_shm_unbounded.c
    ${nacl_SRC_DIR}/trusted/gio/gio_nacl_desc.h
    ${nacl_SRC_DIR}/trusted/gio/gio_nacl_desc.c

    ${nacl_SRC_DIR}/trusted/platform_qualify/linux/nacl_os_qualify.c
    ${nacl_SRC_DIR}/trusted/platform_qualify/linux/sysv_shm_and_mmap.h
    ${nacl_SRC_DIR}/trusted/platform_qualify/linux/sysv_shm_and_mmap.c
    ${nacl_SRC_DIR}/trusted/platform_qualify/arch/x86_64/nacl_dep_qualify_arch.c
    ${nacl_SRC_DIR}/trusted/platform_qualify/posix/nacl_dep_qualify.c

    ${nacl_SRC_DIR}/trusted/nacl_base/nacl_refcount.h
    ${nacl_SRC_DIR}/trusted/nacl_base/nacl_refcount.c

    ${nacl_SRC_DIR}/trusted/nonnacl_util/sel_ldr_launcher.h
    ${nacl_SRC_DIR}/trusted/nonnacl_util/sel_ldr_launcher_base.cc
    ${nacl_SRC_DIR}/trusted/nonnacl_util/sel_ldr_launcher_standalone.cc
    ${nacl_SRC_DIR}/trusted/nonnacl_util/posix/get_plugin_dirname.cc
    ${nacl_SRC_DIR}/trusted/nonnacl_util/posix/sel_ldr_launcher_posix.cc

    ${nacl_SRC_DIR}/trusted/perf_counter/nacl_perf_counter.h
    ${nacl_SRC_DIR}/trusted/perf_counter/nacl_perf_counter.c

    ${nacl_SRC_DIR}/trusted/reverse_service/reverse_service_c.h
    ${nacl_SRC_DIR}/trusted/reverse_service/reverse_service.h
    ${nacl_SRC_DIR}/trusted/reverse_service/reverse_service_c.c
    ${nacl_SRC_DIR}/trusted/reverse_service/reverse_service.cc

    ${nacl_SRC_DIR}/trusted/service_runtime/dyn_array.c
    ${nacl_SRC_DIR}/trusted/service_runtime/elf_util.c
    ${nacl_SRC_DIR}/trusted/service_runtime/env_cleanser.c
    ${nacl_SRC_DIR}/trusted/service_runtime/generic/vm_hole.c
    ${nacl_SRC_DIR}/trusted/service_runtime/linux/nacl_bootstrap_args.c
    ${nacl_SRC_DIR}/trusted/service_runtime/linux/nacl_thread_nice.c
#    ${nacl_SRC_DIR}/trusted/service_runtime/linux/r_debug.c
    ${nacl_SRC_DIR}/trusted/service_runtime/linux/reserved_at_zero.c
    ${nacl_SRC_DIR}/trusted/service_runtime/linux/thread_suspension.c
    ${nacl_SRC_DIR}/trusted/service_runtime/linux/x86/nacl_ldt.c
    ${nacl_SRC_DIR}/trusted/service_runtime/nacl_all_modules.c
    #${nacl_SRC_DIR}/trusted/service_runtime/nacl_app_thread.c // thread is platform specific
    ${nacl_SRC_DIR}/trusted/service_runtime/nacl_bootstrap_channel_error_reporter.c
    ${nacl_SRC_DIR}/trusted/service_runtime/nacl_copy.c
    ${nacl_SRC_DIR}/trusted/service_runtime/nacl_desc_effector_ldr.c
    ${nacl_SRC_DIR}/trusted/service_runtime/nacl_desc_postmessage.c
    ${nacl_SRC_DIR}/trusted/service_runtime/nacl_error_code.c
    ${nacl_SRC_DIR}/trusted/service_runtime/nacl_error_gio.c
    ${nacl_SRC_DIR}/trusted/service_runtime/nacl_error_log_hook.c
    ${nacl_SRC_DIR}/trusted/service_runtime/nacl_globals.c
    ${nacl_SRC_DIR}/trusted/service_runtime/nacl_kernel_service.c
    ${nacl_SRC_DIR}/trusted/service_runtime/nacl_resource.c
    ${nacl_SRC_DIR}/trusted/service_runtime/nacl_reverse_quota_interface.c
    ${nacl_SRC_DIR}/trusted/service_runtime/nacl_secure_service.c
    ${nacl_SRC_DIR}/trusted/service_runtime/nacl_signal_common.c
    ${nacl_SRC_DIR}/trusted/service_runtime/nacl_stack_safety.c
    ${nacl_SRC_DIR}/trusted/service_runtime/nacl_syscall_common.c
    ${nacl_SRC_DIR}/trusted/service_runtime/nacl_syscall_hook.c
    ${nacl_SRC_DIR}/trusted/service_runtime/nacl_text.c
    ${nacl_SRC_DIR}/trusted/service_runtime/nacl_valgrind_hooks.c
    ${nacl_SRC_DIR}/trusted/service_runtime/name_service/default_name_service.c
    ${nacl_SRC_DIR}/trusted/service_runtime/name_service/name_service.c
    ${nacl_SRC_DIR}/trusted/service_runtime/posix/addrspace_teardown.c
    ${nacl_SRC_DIR}/trusted/service_runtime/posix/nacl_signal.c
    ${nacl_SRC_DIR}/trusted/service_runtime/posix/sel_addrspace_posix.c
    ${nacl_SRC_DIR}/trusted/service_runtime/posix/sel_memory.c
    ${nacl_SRC_DIR}/trusted/service_runtime/posix/x86/sel_segments.c
    ${nacl_SRC_DIR}/trusted/service_runtime/sel_addrspace.c
    ${nacl_SRC_DIR}/trusted/service_runtime/sel_ldr.c
    ${nacl_SRC_DIR}/trusted/service_runtime/sel_ldr_standard.c
    ${nacl_SRC_DIR}/trusted/service_runtime/sel_ldr_thread_interface.c
    ${nacl_SRC_DIR}/trusted/service_runtime/sel_main_chrome.c
    ${nacl_SRC_DIR}/trusted/service_runtime/sel_mem.c
    ${nacl_SRC_DIR}/trusted/service_runtime/sel_qualify.c
    ${nacl_SRC_DIR}/trusted/service_runtime/sel_validate_image.c
    ${nacl_SRC_DIR}/trusted/service_runtime/thread_suspension_common.c

    ${nacl_SRC_DIR}/trusted/simple_service/nacl_simple_ltd_service.h
    ${nacl_SRC_DIR}/trusted/simple_service/nacl_simple_ltd_service.c
    ${nacl_SRC_DIR}/trusted/simple_service/nacl_simple_rservice.h
    ${nacl_SRC_DIR}/trusted/simple_service/nacl_simple_rservice.c
    ${nacl_SRC_DIR}/trusted/simple_service/nacl_simple_service.h
    ${nacl_SRC_DIR}/trusted/simple_service/nacl_simple_service.c
    ${nacl_SRC_DIR}/trusted/threading/nacl_thread_interface.h
    ${nacl_SRC_DIR}/trusted/threading/nacl_thread_interface.c
    ${nacl_SRC_DIR}/trusted/validator/validator_init.c
    ${nacl_SRC_DIR}/trusted/weak_ref/weak_ref.cc

    #${nacl_SRC_DIR}/untrusted/nacl/clock.c
    #${nacl_SRC_DIR}/untrusted/nacl/clock_getres.c
    #${nacl_SRC_DIR}/untrusted/nacl/clock_gettime.c
    #${nacl_SRC_DIR}/untrusted/nacl/close.c
    #${nacl_SRC_DIR}/untrusted/nacl/dup.c
    #${nacl_SRC_DIR}/untrusted/nacl/_exit.c
    #${nacl_SRC_DIR}/untrusted/nacl/fstat.c
    #${nacl_SRC_DIR}/untrusted/nacl/getdents.c
    #${nacl_SRC_DIR}/untrusted/nacl/getpid.c
    #${nacl_SRC_DIR}/untrusted/nacl/gettimeofday.c
    #${nacl_SRC_DIR}/untrusted/nacl/lock.c
    #${nacl_SRC_DIR}/untrusted/nacl/lseek.c
    #${nacl_SRC_DIR}/untrusted/nacl/malloc.c
    #${nacl_SRC_DIR}/untrusted/nacl/mmap.c
    #${nacl_SRC_DIR}/untrusted/nacl/munmap.c
    #${nacl_SRC_DIR}/untrusted/nacl/nanosleep.c
    #${nacl_SRC_DIR}/untrusted/nacl/nacl_interface_query.c
    #${nacl_SRC_DIR}/untrusted/nacl/nacl_read_tp.c
    #${nacl_SRC_DIR}/untrusted/nacl/open.c
    #${nacl_SRC_DIR}/untrusted/nacl/read.c
    #${nacl_SRC_DIR}/untrusted/nacl/pthread_initialize_minimal.c
    #${nacl_SRC_DIR}/untrusted/nacl/pthread_stubs.c
    #${nacl_SRC_DIR}/untrusted/nacl/sbrk.c
    #${nacl_SRC_DIR}/untrusted/nacl/sched_yield.c
    #${nacl_SRC_DIR}/untrusted/nacl/stacktrace.c
    #${nacl_SRC_DIR}/untrusted/nacl/start.c
    #${nacl_SRC_DIR}/untrusted/nacl/stat.c
    #${nacl_SRC_DIR}/untrusted/nacl/sysconf.c
    #${nacl_SRC_DIR}/untrusted/nacl/tls.c
    #${nacl_SRC_DIR}/untrusted/nacl/write.c
    #${nacl_SRC_DIR}/untrusted/nacl/gc_hooks.c
    #${nacl_SRC_DIR}/untrusted/nacl/nacl_irt.c
    #${nacl_SRC_DIR}/untrusted/nacl/nacl_tls_get.c
    #${nacl_SRC_DIR}/untrusted/nacl/nacl_tls_init.c
    ${nacl_SRC_DIR}/untrusted/nacl/imc_accept.c
    ${nacl_SRC_DIR}/untrusted/nacl/imc_connect.c
    ${nacl_SRC_DIR}/untrusted/nacl/imc_makeboundsock.c
    ${nacl_SRC_DIR}/untrusted/nacl/imc_mem_obj_create.c
    ${nacl_SRC_DIR}/untrusted/nacl/imc_recvmsg.c
    ${nacl_SRC_DIR}/untrusted/nacl/imc_sendmsg.c
    ${nacl_SRC_DIR}/untrusted/nacl/imc_socketpair.c
    #${nacl_SRC_DIR}/untrusted/nacl/nameservice.c
)

SET(NACL_LINUX 1)
SET(NACL_OSX 0)
SET(NACL_WINDOWS 0)

#ADD_DEFINITIONS(-D__native_client__)
#ADD_DEFINITIONS(-D__LITTLE_ENDIAN__)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-strict-aliasing -Wno-missing-field-initializers -Wextra")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ifany...")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -idirafter ${CMAKE_SOURCE_DIR}/Source/native_client/src/trusted/service_runtime/include")

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/Source
    ${nacl_INCLUDE_DIRECTORIES}
)
ADD_LIBRARY(${nacl_LIBRARY_NAME} SHARED ${nacl_SOURCES})

SET_TARGET_PROPERTIES(${nacl_LIBRARY_NAME} PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR})

INSTALL(TARGETS ${nacl_LIBRARY_NAME} DESTINATION "${LIB_INSTALL_DIR}")
