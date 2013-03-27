CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(nacl_LIBRARY_NAME "nacl")
set(NACLASM_LIBRARY_NAME naclasm)
set(nacl_LIBRARY_NAME ${nacl_LIBRARY_NAME} PARENT_SCOPE)
set(nacl_SRC_DIR "${CMAKE_SOURCE_DIR}/Source/native_client/src")

set(nacl_INCLUDE_DIRECTORIES "${nacl_SRC_DIR}/include/")
set(nacl_INCLUDE_DIRECTORIES ${nacl_INCLUDE_DIRECTORIES} PARENT_SCOPE)

INCLUDE(${nacl_SRC_DIR}/../common.txt)

set(nacl_SOURCES
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

    ${nacl_SRC_DIR}/trusted/fault_injection/fault_injection.c

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
    ${nacl_SRC_DIR}/trusted/platform_qualify/posix/nacl_dep_qualify.c

    ${nacl_SRC_DIR}/trusted/manifest_name_service_proxy/manifest_proxy.c

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

    ${nacl_SRC_DIR}/trusted/service_runtime/linux/nacl_bootstrap_args.c
    ${nacl_SRC_DIR}/trusted/service_runtime/linux/nacl_thread_nice.c
#    ${nacl_SRC_DIR}/trusted/service_runtime/linux/r_debug.c
    ${nacl_SRC_DIR}/trusted/service_runtime/linux/reserved_at_zero.c
    ${nacl_SRC_DIR}/trusted/service_runtime/linux/thread_suspension.c
    ${nacl_SRC_DIR}/trusted/service_runtime/linux/x86/nacl_ldt.c
    # FIXME: Dup nacl_syscall_hook.c, otherwise libnaclasm_service_runtime.a will link error on NaClSyscallCSegHook
    ${nacl_SRC_DIR}/trusted/service_runtime/nacl_syscall_hook.c
    ${nacl_SRC_DIR}/trusted/service_runtime/posix/addrspace_teardown.c
    ${nacl_SRC_DIR}/trusted/service_runtime/posix/nacl_signal.c
    ${nacl_SRC_DIR}/trusted/service_runtime/posix/sel_addrspace_posix.c
    ${nacl_SRC_DIR}/trusted/service_runtime/posix/sel_memory.c
    ${nacl_SRC_DIR}/trusted/service_runtime/posix/x86/sel_segments.c

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

set(VALIDATOR_X86_SOURCES
    ${nacl_SRC_DIR}/trusted/cpu_features/arch/x86/cpu_x86.c
    ${nacl_SRC_DIR}/trusted/validator/x86/error_reporter.c
    ${nacl_SRC_DIR}/trusted/validator/x86/error_reporter_verbose.c
    ${nacl_SRC_DIR}/trusted/validator/x86/halt_trim.c
    ${nacl_SRC_DIR}/trusted/validator/x86/ncinstbuffer.c
    ${nacl_SRC_DIR}/trusted/validator/x86/ncinstbuffer_inl.c
    ${nacl_SRC_DIR}/trusted/validator/x86/nc_segment.c
    ${nacl_SRC_DIR}/trusted/validator/x86/decoder/ncdis_decode_tables.c
    ${nacl_SRC_DIR}/trusted/validator/x86/decoder/nc_inst_iter.c
    ${nacl_SRC_DIR}/trusted/validator/x86/decoder/nc_inst_state.c
    ${nacl_SRC_DIR}/trusted/validator/x86/decoder/nc_inst_state_statics.c
    ${nacl_SRC_DIR}/trusted/validator/x86/decoder/nc_inst_trans.c
    ${nacl_SRC_DIR}/trusted/validator/x86/decoder/ncopcode_desc.c
    ${nacl_SRC_DIR}/trusted/validator/x86/decoder/ncopcode_desc_verbose.c
    ${nacl_SRC_DIR}/trusted/validator/x86/decoder/ncop_exps.c
    ${nacl_SRC_DIR}/trusted/validator/x86/x86_insts.c
    ${nacl_SRC_DIR}/trusted/validator/x86/x86_insts_inl.c
    ${nacl_SRC_DIR}/trusted/validator/x86/x86_insts_verbose.c
    ${nacl_SRC_DIR}/trusted/validator/x86/ncval_reg_sfi/address_sets.c
    #${nacl_SRC_DIR}/trusted/validator/x86/ncval_reg_sfi/address_sets_inl.c
    ${nacl_SRC_DIR}/trusted/validator/x86/ncval_reg_sfi/nc_cpu_checks.c
    ${nacl_SRC_DIR}/trusted/validator/x86/ncval_reg_sfi/nc_illegal.c
    ${nacl_SRC_DIR}/trusted/validator/x86/ncval_reg_sfi/nc_jumps.c
    ${nacl_SRC_DIR}/trusted/validator/x86/ncval_reg_sfi/nc_jumps_detailed.c
    ${nacl_SRC_DIR}/trusted/validator/x86/ncval_reg_sfi/nc_memory_protect.c
    ${nacl_SRC_DIR}/trusted/validator/x86/ncval_reg_sfi/nc_opcode_histogram.c
    ${nacl_SRC_DIR}/trusted/validator/x86/ncval_reg_sfi/nc_postconds.c
    ${nacl_SRC_DIR}/trusted/validator/x86/ncval_reg_sfi/nc_protect_base.c
    ${nacl_SRC_DIR}/trusted/validator/x86/ncval_reg_sfi/ncval_decode_tables.c
    ${nacl_SRC_DIR}/trusted/validator/x86/ncval_reg_sfi/ncvalidate_iter.c
    ${nacl_SRC_DIR}/trusted/validator/x86/ncval_reg_sfi/ncvalidate_iter_detailed.c
    ${nacl_SRC_DIR}/trusted/validator/x86/ncval_reg_sfi/ncvalidate_iter_verbose.c
    ${nacl_SRC_DIR}/trusted/validator/x86/ncval_reg_sfi/ncvalidate_utils.c
    ${nacl_SRC_DIR}/trusted/validator_x86/nccopycode.c
    #${nacl_SRC_DIR}/trusted/validator_x86/ncdis.c
    #${nacl_SRC_DIR}/trusted/validator_x86/ncdis_decode_tables.c
    #${nacl_SRC_DIR}/trusted/validator_x86/ncdis_segments.c
    #${nacl_SRC_DIR}/trusted/validator_x86/ncenuminsts_x86_32.c
    #${nacl_SRC_DIR}/trusted/validator_x86/ncenuminsts_x86_64.c
    #${nacl_SRC_DIR}/trusted/validator_x86/nc_read_segment.c
    #${nacl_SRC_DIR}/trusted/validator_x86/ncval.c
)

if (${TARGET_ARCH} STREQUAL "x86_64")
    set(ASM_S_INPUT_FILES 
        ${NATIVE_CLIENT_DIR}/src/trusted/cpu_features/arch/x86/cpu_xgetbv
        ${NATIVE_CLIENT_DIR}/src/trusted/validator_x86/nccopycode_stores
    )
    list(APPEND nacl_SOURCES
        ${VALIDATOR_X86_SOURCES}
        ${nacl_SRC_DIR}/trusted/validator/x86/64/ncvalidate.c
        ${nacl_SRC_DIR}/trusted/validator/x86/64/ncvalidate_verbose.c
        ${nacl_SRC_DIR}/trusted/platform_qualify/arch/x86/nacl_cpuwhitelist.c
        ${nacl_SRC_DIR}/trusted/platform_qualify/arch/x86/vcpuid.c
        ${nacl_SRC_DIR}/trusted/platform_qualify/arch/x86_64/nacl_dep_qualify_arch.c
    )
elseif (${TARGET_ARCH} STREQUAL "i386")
    set(ASM_S_INPUT_FILES 
        ${NATIVE_CLIENT_DIR}/src/trusted/cpu_features/arch/x86/cpu_xgetbv
        ${NATIVE_CLIENT_DIR}/src/trusted/validator_x86/nccopycode_stores
    )
    list(APPEND nacl_SOURCES
        ${VALIDATOR_X86_SOURCES}
        ${nacl_SRC_DIR}/trusted/validator/x86/32/ncvalidate.c
        ${nacl_SRC_DIR}/trusted/validator/x86/32/ncvalidate_verbose.c
        ${nacl_SRC_DIR}/trusted/platform_qualify/arch/x86/nacl_cpuwhitelist.c
        ${nacl_SRC_DIR}/trusted/platform_qualify/arch/x86/vcpuid.c
        ${nacl_SRC_DIR}/trusted/platform_qualify/arch/x86_32/nacl_dep_qualify_arch.c
    )
elseif (${TARGET_ARCH} MATCHES "^arm*")
    list(APPEND nacl_SOURCES
        ${nacl_SRC_DIR}/trusted/validator_arm/address_set.cc
        ${nacl_SRC_DIR}/trusted/validator_arm/actual_classes.cc
        ${nacl_SRC_DIR}/trusted/validator_arm/baseline_classes.cc
        ${nacl_SRC_DIR}/trusted/validator_arm/inst_classes.cc
        ${nacl_SRC_DIR}/trusted/validator_arm/model.cc
        ${nacl_SRC_DIR}/trusted/validator_arm/validator.cc
        ${nacl_SRC_DIR}/trusted/validator_arm/gen/arm32_decode.cc
        ${nacl_SRC_DIR}/trusted/validator_arm/gen/arm32_decode_actuals_1.cc
        ${nacl_SRC_DIR}/trusted/validator_arm/gen/arm32_decode_actuals_2.cc
        ${nacl_SRC_DIR}/trusted/validator_arm/ncvalidate.cc
        ${nacl_SRC_DIR}/trusted/platform_qualify/arch/arm/nacl_dep_qualify_arch.c
        ${nacl_SRC_DIR}/trusted/platform_qualify/arch/arm/nacl_qualify_fpu.c
    )
endif ()


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-strict-aliasing -Wno-missing-field-initializers -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-strict-aliasing -Wno-missing-field-initializers -Wextra")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -idirafter ${CMAKE_SOURCE_DIR}/Source/native_client/src/trusted/service_runtime/include")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -idirafter ${CMAKE_SOURCE_DIR}/Source/native_client/src/trusted/service_runtime/include")

# Add asm sources
add_custom_target(asm_precompile)
foreach (ASM_S ${ASM_S_INPUT_FILES})
    add_custom_command(
        OUTPUT ${ASM_S}.s
        COMMAND cpp
        ARGS -I${NATIVE_CLIENT_DIR}/.. ${CPP_PRECOMPILE_FLAGS} ${ASM_S}.S ${ASM_S}.s
        DEPENDS ${ASM_S}.S
    )
    list(APPEND ASM_s_SOURCES ${ASM_S}.s)
    add_dependencies(asm_precompile ${ASM_S}.s)
endforeach ()

enable_language(ASM-ATT)
add_library(${NACLASM_LIBRARY_NAME} STATIC ${ASM_s_SOURCES})
add_dependencies(${NACLASM_LIBRARY_NAME} asm_precompile)

set(nacl_LIBRARIES
  ${NACLASM_LIBRARY_NAME}
  ${NACL_SEL_LIBRARY_NAME}
)

include_directories(
    ${CMAKE_SOURCE_DIR}/Source
    ${nacl_INCLUDE_DIRECTORIES}
)
add_library(${nacl_LIBRARY_NAME} STATIC ${nacl_SOURCES})
set_target_properties(${nacl_LIBRARY_NAME} PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR} COMPILE_FLAGS "-fPIC")
target_link_libraries(${nacl_LIBRARY_NAME} ${nacl_LIBRARIES})

install(TARGETS ${nacl_LIBRARY_NAME} DESTINATION "${LIB_INSTALL_DIR}")
