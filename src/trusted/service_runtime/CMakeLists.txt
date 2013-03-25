set(NACLASM_LIBRARY_NAME naclasm)

set(NACL_SEL_LIBRARY_SOURCES
    ${NATIVE_CLIENT_DIR}/src/trusted/debug_stub/abi.cc
    ${NATIVE_CLIENT_DIR}/src/trusted/debug_stub/debug_stub.cc
    ${NATIVE_CLIENT_DIR}/src/trusted/debug_stub/nacl_debug.cc
    ${NATIVE_CLIENT_DIR}/src/trusted/debug_stub/packet.cc
    ${NATIVE_CLIENT_DIR}/src/trusted/debug_stub/posix/debug_stub_posix.cc
    ${NATIVE_CLIENT_DIR}/src/trusted/debug_stub/posix/platform_impl.cc
    ${NATIVE_CLIENT_DIR}/src/trusted/debug_stub/posix/thread_impl.cc
    ${NATIVE_CLIENT_DIR}/src/trusted/debug_stub/session.cc
    ${NATIVE_CLIENT_DIR}/src/trusted/debug_stub/target.cc
    ${NATIVE_CLIENT_DIR}/src/trusted/debug_stub/thread_common.cc
    ${NATIVE_CLIENT_DIR}/src/trusted/debug_stub/transport_common.cc
    ${NATIVE_CLIENT_DIR}/src/trusted/debug_stub/util.cc
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/dyn_array.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/elf_util.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/nacl_all_modules.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/nacl_app_thread.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/nacl_bootstrap_channel_error_reporter.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/nacl_copy.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/nacl_desc_effector_ldr.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/nacl_desc_postmessage.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/nacl_error_gio.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/nacl_error_log_hook.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/nacl_globals.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/nacl_kernel_service.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/nacl_resource.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/nacl_reverse_quota_interface.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/nacl_secure_service.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/nacl_signal_common.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/nacl_stack_safety.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/nacl_syscall_common.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/nacl_syscall_hook.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/nacl_text.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/nacl_valgrind_hooks.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/name_service/default_name_service.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/name_service/name_service.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/sel_addrspace.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/sel_ldr.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/sel_ldr_standard.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/sel_ldr_thread_interface.c
    #TODO(mseaborn): Move sel_main_chrome.c to the
    #"sel_main_chrome" library once Chromium is changed to
    #depend on that rather than on "sel".
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/sel_main_chrome.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/sel_mem.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/sel_qualify.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/sel_validate_image.c
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/thread_suspension_common.c
    # nacl_error_code
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/nacl_error_code.c
    # env_cleanser
    ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/env_cleanser.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/validator_init.c
)

set(VALIDATOR_X86_SOURCES
    ${NATIVE_CLIENT_DIR}/src/trusted/cpu_features/arch/x86/cpu_x86.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/64/ncvalidate.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/64/ncvalidate_verbose.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/error_reporter.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/error_reporter_verbose.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/halt_trim.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/ncinstbuffer.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/ncinstbuffer_inl.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/nc_segment.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/decoder/ncdis_decode_tables.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/decoder/nc_inst_iter.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/decoder/nc_inst_state.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/decoder/nc_inst_state_statics.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/decoder/nc_inst_trans.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/decoder/ncopcode_desc.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/decoder/ncopcode_desc_verbose.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/decoder/ncop_exps.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/x86_insts.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/x86_insts_inl.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/x86_insts_verbose.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/ncval_reg_sfi/address_sets.c
    #${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/ncval_reg_sfi/address_sets_inl.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/ncval_reg_sfi/nc_cpu_checks.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/ncval_reg_sfi/nc_illegal.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/ncval_reg_sfi/nc_jumps.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/ncval_reg_sfi/nc_jumps_detailed.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/ncval_reg_sfi/nc_memory_protect.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/ncval_reg_sfi/nc_opcode_histogram.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/ncval_reg_sfi/nc_postconds.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/ncval_reg_sfi/nc_protect_base.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/ncval_reg_sfi/ncval_decode_tables.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/ncval_reg_sfi/ncvalidate_iter.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/ncval_reg_sfi/ncvalidate_iter_detailed.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/ncval_reg_sfi/ncvalidate_iter_verbose.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/ncval_reg_sfi/ncvalidate_utils.c
)

include(${NATIVE_CLIENT_DIR}/common.txt)

if (${TARGET_ARCH} STREQUAL "x86_64")
    add_definitions(-DNACL_X86_64_ZERO_BASED_SANDBOX=0 -D_GNU_SOURCE=1)
    set(ASM_S_INPUT_FILES 
        ${NATIVE_CLIENT_DIR}/src/trusted/cpu_features/arch/x86/cpu_xgetbv
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/x86_64/nacl_switch_64
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/x86_64/nacl_syscall_64
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/x86_64/tramp_64
    )
    list(APPEND NACL_SEL_LIBRARY_SOURCES
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/x86/nacl_ldt_x86.c
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/x86_64/nacl_app_64.c
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/x86_64/nacl_switch_to_app_64.c
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/x86_64/nacl_tls_64.c
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/x86_64/sel_addrspace_posix_x86_64.c
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/x86_64/sel_ldr_x86_64.c
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/x86_64/sel_rt_64.c
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/linux/nacl_signal_64.c
    )
    list(APPEND NACL_SEL_LIBRARY_SOURCES
        ${VALIDATOR_X86_SOURCES}
        ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/64/ncvalidate.c
        ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/64/ncvalidate_verbose.c
    )
elseif (${TARGET_ARCH} STREQUAL "i386")
    set(ASM_S_INPUT_FILES 
        ${NATIVE_CLIENT_DIR}/src/trusted/cpu_features/arch/x86/cpu_xgetbv
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/x86_32/nacl_switch_32
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/x86_32/nacl_syscall_32
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/x86_32/springboard
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/x86_32/tramp_32
    )
    list(APPEND NACL_SEL_LIBRARY_SOURCES
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/x86/nacl_ldt_x86.c
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/x86_32/nacl_app_32.c
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/x86_32/nacl_switch_to_app_32.c
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/x86_32/nacl_tls_32.c
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/x86_32/sel_addrspace_x86_32.c
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/x86_32/sel_ldr_x86_32.c
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/x86_32/sel_rt_32.c
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/linux/nacl_signal_32.c
    )
    list(APPEND NACL_SEL_LIBRARY_SOURCES
        ${VALIDATOR_X86_SOURCES}
        ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/32/ncvalidate.c
        ${NATIVE_CLIENT_DIR}/src/trusted/validator/x86/32/ncvalidate_verbose.c
    )
elseif (${TARGET_ARCH} MATCHES "^arm*")
    set(ASM_S_INPUT_FILES 
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/arm/nacl_switch_arm
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/arm/nacl_syscall_arm
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/arm/tramp_32
    )
    list(APPEND NACL_SEL_LIBRARY_SOURCES
        ${NATIVE_CLIENT_DIR}/src/trusted/cpu_features/arch/arm/cpu_arm.c
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/arm/nacl_app.c
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/arm/nacl_switch_to_app_arm.c
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/arm/nacl_tls.c
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/arm/sel_addrspace_arm.c
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/arm/sel_ldr_arm.c
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/arch/arm/sel_rt.c
        ${NATIVE_CLIENT_DIR}/src/trusted/service_runtime/linux/nacl_signal_arm.c
        ${NATIVE_CLIENT_DIR}/src/trusted/validator_arm/address_set.cc
        ${NATIVE_CLIENT_DIR}/src/trusted/validator_arm/actual_classes.cc
        ${NATIVE_CLIENT_DIR}/src/trusted/validator_arm/baseline_classes.cc
        ${NATIVE_CLIENT_DIR}/src/trusted/validator_arm/inst_classes.cc
        ${NATIVE_CLIENT_DIR}/src/trusted/validator_arm/model.cc
        ${NATIVE_CLIENT_DIR}/src/trusted/validator_arm/validator.cc
        ${NATIVE_CLIENT_DIR}/src/trusted/validator_arm/gen/arm32_decode.cc
        ${NATIVE_CLIENT_DIR}/src/trusted/validator_arm/gen/arm32_decode_actuals_1.cc
        ${NATIVE_CLIENT_DIR}/src/trusted/validator_arm/gen/arm32_decode_actuals_2.cc
        ${NATIVE_CLIENT_DIR}/src/trusted/validator_arm/ncvalidate.cc
    )
endif ()

set(NACL_SEL_INCLUDE_DIRECTORIES
    ${NATIVE_CLIENT_DIR}/..
    ${NATIVE_CLIENT_DIR}/src/third_party
)

set(NACL_SEL_LIBRARY_LIBRARIES
    ${nacl_LIBRARY_NAME}
    ${NACLASM_LIBRARY_NAME}
)

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

include_directories(${NACL_SEL_INCLUDE_DIRECTORIES})
add_library(${NACL_SEL_LIBRARY_NAME} STATIC ${NACL_SEL_LIBRARY_SOURCES})
set_target_properties(${NACL_SEL_LIBRARY_NAME} PROPERTIES COMPILE_FLAGS "-fPIC")
target_link_libraries(${NACL_SEL_LIBRARY_NAME} ${NACL_SEL_LIBRARY_LIBRARIES})
