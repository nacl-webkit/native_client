CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(NACL_ALL_LIBRARY_NAME ${NACL_ALL_LIBRARY_NAME} PARENT_SCOPE)
set(NACLASM_LIBRARY_NAME naclasm)

set(NACL_ALL_LIBRARY_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set(NACL_ALL_LIBRARY_INCLUDE_DIRECTORIES ${NACL_ALL_LIBRARY_INCLUDE_DIRECTORIES} PARENT_SCOPE)

set(NACL_ALL_LIBRARY_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/shared/imc/nacl_imc_c.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/shared/imc/nacl_imc_common.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/shared/imc/nacl_imc.h
    ${CMAKE_CURRENT_SOURCE_DIR}/shared/imc/nacl_imc_c.h
    ${CMAKE_CURRENT_SOURCE_DIR}/shared/imc/linux/nacl_imc.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/shared/imc/posix/nacl_imc_posix.cc

    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/debug_stub/abi.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/debug_stub/debug_stub.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/debug_stub/nacl_debug.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/debug_stub/packet.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/debug_stub/posix/debug_stub_posix.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/debug_stub/posix/platform_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/debug_stub/posix/thread_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/debug_stub/session.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/debug_stub/target.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/debug_stub/thread_common.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/debug_stub/transport_common.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/debug_stub/util.cc

    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_base.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_base.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_cond.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_cond.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_custom.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_custom.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_dir.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_dir.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_effector.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_effector_trusted_mem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_effector_trusted_mem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_imc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_imc.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_imc_shm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_imc_shm.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_invalid.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_invalid.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_io.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_io.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_mutex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_mutex.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_null.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_null.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_rng.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_rng.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_quota.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_quota.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_quota_interface.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_quota_interface.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_semaphore.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_semaphore.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_sync_socket.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_sync_socket.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nacl_desc_wrapper.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nrd_all_modules.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nrd_all_modules.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nrd_xfer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nrd_xfer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/nrd_xfer_intern.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/linux/nacl_desc_sysv_shm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/linux/nacl_desc_sysv_shm.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/posix/nacl_desc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/posix/nacl_desc_conn_cap.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/posix/nacl_desc_imc_bound_desc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/desc/posix/nacl_makeboundsock.c

    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/fault_injection/fault_injection.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/fault_injection/test_injection.c

    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/interval_multiset/nacl_interval_range_tree.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/interval_multiset/nacl_interval_multiset_delete.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/interval_multiset/nacl_interval_list.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/interval_multiset/nacl_interval_multiset_factory.c

    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/gio/gio_shm.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/gio/gio_shm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/gio/gio_shm_unbounded.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/gio/gio_shm_unbounded.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/gio/gio_nacl_desc.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/gio/gio_nacl_desc.c

    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/platform_qualify/linux/nacl_os_qualify.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/platform_qualify/linux/sysv_shm_and_mmap.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/platform_qualify/linux/sysv_shm_and_mmap.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/platform_qualify/posix/nacl_dep_qualify.c

    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/manifest_name_service_proxy/manifest_proxy.c

    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/nacl_base/nacl_refcount.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/nacl_base/nacl_refcount.c

    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/nonnacl_util/sel_ldr_launcher.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/nonnacl_util/sel_ldr_launcher_base.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/nonnacl_util/sel_ldr_launcher_standalone.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/nonnacl_util/posix/get_plugin_dirname.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/nonnacl_util/posix/sel_ldr_launcher_posix.cc

    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/perf_counter/nacl_perf_counter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/perf_counter/nacl_perf_counter.c

    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/reverse_service/reverse_service_c.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/reverse_service/reverse_service.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/reverse_service/reverse_service_c.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/reverse_service/reverse_service.cc

    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/service_runtime/linux/nacl_bootstrap_args.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/service_runtime/linux/nacl_thread_nice.c
    #${CMAKE_CURRENT_SOURCE_DIR}/trusted/service_runtime/linux/r_debug.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/service_runtime/linux/reserved_at_zero.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/service_runtime/linux/thread_suspension.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/service_runtime/linux/x86/nacl_ldt.c
    # FIXME: Dup nacl_syscall_hook.c, otherwise libnaclasm_service_runtime.a will link error on NaClSyscallCSegHook
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/service_runtime/nacl_syscall_hook.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/service_runtime/posix/addrspace_teardown.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/service_runtime/posix/nacl_signal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/service_runtime/posix/sel_addrspace_posix.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/service_runtime/posix/sel_memory.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/service_runtime/posix/x86/sel_segments.c

    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/simple_service/nacl_simple_ltd_service.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/simple_service/nacl_simple_ltd_service.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/simple_service/nacl_simple_rservice.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/simple_service/nacl_simple_rservice.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/simple_service/nacl_simple_service.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/simple_service/nacl_simple_service.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/threading/nacl_thread_interface.h
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/threading/nacl_thread_interface.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/validator_init.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/weak_ref/weak_ref.cc
)

set(VALIDATOR_X86_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/cpu_features/arch/x86/cpu_x86.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/error_reporter.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/error_reporter_verbose.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/halt_trim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/ncinstbuffer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/ncinstbuffer_inl.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/nc_segment.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/decoder/ncdis_decode_tables.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/decoder/nc_inst_iter.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/decoder/nc_inst_state.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/decoder/nc_inst_state_statics.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/decoder/nc_inst_trans.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/decoder/ncopcode_desc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/decoder/ncopcode_desc_verbose.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/decoder/ncop_exps.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/x86_insts.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/x86_insts_inl.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/x86_insts_verbose.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/ncval_reg_sfi/address_sets.c
    #${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/ncval_reg_sfi/address_sets_inl.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/ncval_reg_sfi/nc_cpu_checks.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/ncval_reg_sfi/nc_illegal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/ncval_reg_sfi/nc_jumps.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/ncval_reg_sfi/nc_jumps_detailed.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/ncval_reg_sfi/nc_memory_protect.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/ncval_reg_sfi/nc_opcode_histogram.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/ncval_reg_sfi/nc_postconds.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/ncval_reg_sfi/nc_protect_base.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/ncval_reg_sfi/ncval_decode_tables.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/ncval_reg_sfi/ncvalidate_iter.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/ncval_reg_sfi/ncvalidate_iter_detailed.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/ncval_reg_sfi/ncvalidate_iter_verbose.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/ncval_reg_sfi/ncvalidate_utils.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator_x86/nccopycode.c
    #${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator_x86/ncdis.c
    #${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator_x86/ncdis_decode_tables.c
    #${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator_x86/ncdis_segments.c
    #${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator_x86/ncenuminsts_x86_32.c
    #${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator_x86/ncenuminsts_x86_64.c
    #${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator_x86/nc_read_segment.c
    #${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator_x86/ncval.c
)

if (${TARGET_ARCH} STREQUAL "x86_64")
    set(ASM_S_INPUT_FILES 
        ${NATIVE_CLIENT_DIR}/src/trusted/cpu_features/arch/x86/cpu_xgetbv
        ${NATIVE_CLIENT_DIR}/src/trusted/validator_x86/nccopycode_stores
    )
    list(APPEND NACL_ALL_LIBRARY_SOURCES
        ${VALIDATOR_X86_SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/64/ncvalidate.c
        ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/64/ncvalidate_verbose.c
        ${CMAKE_CURRENT_SOURCE_DIR}/trusted/platform_qualify/arch/x86/nacl_cpuwhitelist.c
        ${CMAKE_CURRENT_SOURCE_DIR}/trusted/platform_qualify/arch/x86/vcpuid.c
        ${CMAKE_CURRENT_SOURCE_DIR}/trusted/platform_qualify/arch/x86_64/nacl_dep_qualify_arch.c
    )
elseif (${TARGET_ARCH} STREQUAL "i386")
    set(ASM_S_INPUT_FILES 
        ${NATIVE_CLIENT_DIR}/src/trusted/cpu_features/arch/x86/cpu_xgetbv
        ${NATIVE_CLIENT_DIR}/src/trusted/validator_x86/nccopycode_stores
    )
    list(APPEND NACL_ALL_LIBRARY_SOURCES
        ${VALIDATOR_X86_SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/32/ncvalidate.c
        ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator/x86/32/ncvalidate_verbose.c
        ${CMAKE_CURRENT_SOURCE_DIR}/trusted/platform_qualify/arch/x86/nacl_cpuwhitelist.c
        ${CMAKE_CURRENT_SOURCE_DIR}/trusted/platform_qualify/arch/x86/vcpuid.c
        ${CMAKE_CURRENT_SOURCE_DIR}/trusted/platform_qualify/arch/x86_32/nacl_dep_qualify_arch.c
    )
elseif (${TARGET_ARCH} MATCHES "^arm*")
    list(APPEND NACL_ALL_LIBRARY_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator_arm/address_set.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator_arm/actual_classes.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator_arm/baseline_classes.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator_arm/inst_classes.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator_arm/model.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator_arm/validator.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator_arm/gen/arm32_decode.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator_arm/gen/arm32_decode_actuals_1.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator_arm/gen/arm32_decode_actuals_2.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/trusted/validator_arm/ncvalidate.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/trusted/platform_qualify/arch/arm/nacl_dep_qualify_arch.c
        ${CMAKE_CURRENT_SOURCE_DIR}/trusted/platform_qualify/arch/arm/nacl_qualify_fpu.c
    )
endif ()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-strict-aliasing -Wno-missing-field-initializers -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-strict-aliasing -Wno-missing-field-initializers -Wextra")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -idirafter ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/include")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -idirafter ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/include")

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

set(NACL_ALL_LIBRARIES
  ${NACLASM_LIBRARY_NAME}
  ${NACL_SEL_LIBRARY_NAME}
  nonnacl_srpc
  nacl_shared_platform
  nacl_shared_gio
)

include_directories(
    ${CHROME_DEPS_DIR}
    ${NACL_ALL_LIBRARY_INCLUDE_DIRECTORIES}
)
add_library(${NACL_ALL_LIBRARY_NAME} STATIC ${NACL_ALL_LIBRARY_SOURCES})
set_target_properties(${NACL_ALL_LIBRARY_NAME} PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR} COMPILE_FLAGS "-fPIC")
target_link_libraries(${NACL_ALL_LIBRARY_NAME} ${NACL_ALL_LIBRARIES})

include(${NATIVE_CLIENT_DIR}/tools.txt)

install(TARGETS ${NACL_ALL_LIBRARY_NAME} DESTINATION "${LIB_INSTALL_DIR}")
