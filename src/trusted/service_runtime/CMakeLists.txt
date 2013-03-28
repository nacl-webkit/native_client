set(NACLASM_SERVICE_RUNTIME_LIBRARY_NAME naclasm_service_runtime)
set(NACL_GENNED_SYSCALL_HANDLER nacl_genned_syscall_handler)

set(NACL_SEL_LIBRARY_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/dyn_array.c
    ${CMAKE_CURRENT_SOURCE_DIR}/elf_util.c
    ${CMAKE_CURRENT_SOURCE_DIR}/generic/vm_hole.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_all_modules.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_app_thread.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_bootstrap_channel_error_reporter.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_copy.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_desc_effector_ldr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_desc_postmessage.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_error_gio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_error_log_hook.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_globals.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_kernel_service.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_resource.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_reverse_quota_interface.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_secure_service.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_signal_common.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_stack_safety.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_syscall_common.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_syscall_hook.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_text.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_valgrind_hooks.c
    ${CMAKE_CURRENT_SOURCE_DIR}/name_service/default_name_service.c
    ${CMAKE_CURRENT_SOURCE_DIR}/name_service/name_service.c
    ${CMAKE_CURRENT_SOURCE_DIR}/sel_addrspace.c
    ${CMAKE_CURRENT_SOURCE_DIR}/sel_ldr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/sel_ldr_standard.c
    ${CMAKE_CURRENT_SOURCE_DIR}/sel_ldr_thread_interface.c
    #TODO(mseaborn): Move sel_main_chrome.c to the
    #"sel_main_chrome" library once Chromium is changed to
    #depend on that rather than on "sel".
    ${CMAKE_CURRENT_SOURCE_DIR}/sel_main_chrome.c
    ${CMAKE_CURRENT_SOURCE_DIR}/sel_mem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/sel_qualify.c
    ${CMAKE_CURRENT_SOURCE_DIR}/sel_validate_image.c
    ${CMAKE_CURRENT_SOURCE_DIR}/thread_suspension_common.c
    # nacl_error_code
    ${CMAKE_CURRENT_SOURCE_DIR}/nacl_error_code.c
    # env_cleanser
    ${CMAKE_CURRENT_SOURCE_DIR}/env_cleanser.c
    ${NATIVE_CLIENT_DIR}/src/trusted/validator/validator_init.c
)

if (${TARGET_ARCH} STREQUAL "x86_64")
    add_definitions(-DNACL_X86_64_ZERO_BASED_SANDBOX=0 -D_GNU_SOURCE=1)
    set(ASM_S_INPUT_FILES 
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/x86_64/nacl_switch_64
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/x86_64/nacl_syscall_64
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/x86_64/tramp_64
    )
    list(APPEND NACL_SEL_LIBRARY_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/x86/nacl_ldt_x86.c
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/x86_64/nacl_app_64.c
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/x86_64/nacl_switch_to_app_64.c
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/x86_64/nacl_tls_64.c
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/x86_64/sel_addrspace_posix_x86_64.c
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/x86_64/sel_ldr_x86_64.c
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/x86_64/sel_rt_64.c
        ${CMAKE_CURRENT_SOURCE_DIR}/linux/nacl_signal_64.c
    )
elseif (${TARGET_ARCH} STREQUAL "i386")
    set(ASM_S_INPUT_FILES 
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/x86_32/nacl_switch_32
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/x86_32/nacl_syscall_32
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/x86_32/springboard
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/x86_32/tramp_32
    )
    list(APPEND NACL_SEL_LIBRARY_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/x86/nacl_ldt_x86.c
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/x86_32/nacl_app_32.c
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/x86_32/nacl_switch_to_app_32.c
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/x86_32/nacl_tls_32.c
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/x86_32/sel_addrspace_x86_32.c
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/x86_32/sel_ldr_x86_32.c
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/x86_32/sel_rt_32.c
        ${CMAKE_CURRENT_SOURCE_DIR}/linux/nacl_signal_32.c
    )
elseif (${TARGET_ARCH} MATCHES "^arm*")
    set(ASM_S_INPUT_FILES 
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/arm/nacl_switch_arm
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/arm/nacl_syscall_arm
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/arm/tramp_32
    )
    list(APPEND NACL_SEL_LIBRARY_SOURCES
        ${NATIVE_CLIENT_DIR}/src/trusted/cpu_features/arch/arm/cpu_arm.c
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/arm/nacl_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/arm/nacl_switch_to_app_arm.c
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/arm/nacl_tls.c
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/arm/sel_addrspace_arm.c
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/arm/sel_ldr_arm.c
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/arm/sel_rt.c
        ${CMAKE_CURRENT_SOURCE_DIR}/linux/nacl_signal_arm.c
    )
endif ()

set(NACL_SEL_INCLUDE_DIRECTORIES
    ${NATIVE_CLIENT_DIR}/..
    ${NATIVE_CLIENT_DIR}/src/third_party
)

# Add asm sources
add_custom_target(asm_service_runtime_precompile)
foreach (ASM_S ${ASM_S_INPUT_FILES})
    add_custom_command(
        OUTPUT ${ASM_S}.s
        COMMAND cpp
        ARGS -I${NATIVE_CLIENT_DIR}/.. ${CPP_PRECOMPILE_FLAGS} ${ASM_S}.S ${ASM_S}.s
        DEPENDS ${ASM_S}.S
    )
    list(APPEND ASM_s_SOURCES ${ASM_S}.s)
    add_dependencies(asm_service_runtime_precompile ${ASM_S}.s)
endforeach ()

enable_language(ASM-ATT)
add_library(${NACLASM_SERVICE_RUNTIME_LIBRARY_NAME} STATIC ${ASM_s_SOURCES})
add_dependencies(${NACLASM_SERVICE_RUNTIME_LIBRARY_NAME} asm_service_runtime_precompile)

# Generate syscall handler code
set(syscall_handlers_output ${CMAKE_CURRENT_SOURCE_DIR}/posix/nacl_syscall_handlers.c)
add_custom_target(gen_nacl_syscall_handler)
add_custom_command(
    OUTPUT ${syscall_handlers_output}
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/nacl_syscall_handlers_gen.py
    ARGS -i ${CMAKE_CURRENT_SOURCE_DIR}/posix/nacl_syscall_impl.c -o ${syscall_handlers_output}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/posix/nacl_syscall_impl.c
)
add_dependencies(gen_nacl_syscall_handler ${syscall_handlers_output})

add_library(${NACL_GENNED_SYSCALL_HANDLER} STATIC ${syscall_handlers_output})
set_target_properties(${NACL_GENNED_SYSCALL_HANDLER} PROPERTIES COMPILE_FLAGS "-fPIC")
add_dependencies(${NACL_GENNED_SYSCALL_HANDLER} gen_nacl_syscall_handler)

include_directories(${NACL_SEL_INCLUDE_DIRECTORIES})
add_library(${NACL_SEL_LIBRARY_NAME} STATIC ${NACL_SEL_LIBRARY_SOURCES})
set_target_properties(${NACL_SEL_LIBRARY_NAME} PROPERTIES COMPILE_FLAGS "-fPIC")
target_link_libraries(${NACL_SEL_LIBRARY_NAME} ${NACLASM_SERVICE_RUNTIME_LIBRARY_NAME} ${NACL_GENNED_SYSCALL_HANDLER})
