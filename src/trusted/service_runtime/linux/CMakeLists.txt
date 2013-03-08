set(NACL_BOOTSTRAP_LIBRARY_NAME nacl_bootstrap_lib)
set(NACL_BOOTSTRAP_MUNGE_PHDR_NAME nacl_bootstrap_munge_phdr)
set(NACL_BOOTSTRAP_RAW nacl_bootstrap_raw)
set(NACL_HELPER_BOOTSTRAP nacl_helper_bootstrap)

include(${NATIVE_CLIENT_DIR}/common.txt)

include_directories("${CMAKE_SOURCE_DIR}/Source/chrome_deps")
add_library(${NACL_BOOTSTRAP_LIBRARY_NAME} STATIC "nacl_bootstrap.c")
set_target_properties(${NACL_BOOTSTRAP_LIBRARY_NAME}
    PROPERTIES INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/Source/chrome_deps
    COMPILE_FLAGS "-fno-builtin -fno-stack-protector -fno-pic -fno-PIC -fno-pie -fno-PIE"
)

add_executable(${NACL_BOOTSTRAP_MUNGE_PHDR_NAME} "nacl_bootstrap_munge_phdr.c")
target_link_libraries(${NACL_BOOTSTRAP_MUNGE_PHDR_NAME} "-lelf") 

add_custom_target(${NACL_BOOTSTRAP_RAW} ALL
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/ld_bfd.py --compiler g++ -m ${LINKER_EMULATION} --build-id -static --defsym RESERVE_TOP=${NACL_RESERVE_TOP} --script=${CMAKE_CURRENT_SOURCE_DIR}/nacl_bootstrap.x -o ${CMAKE_BINARY_DIR}/bin/${NACL_BOOTSTRAP_RAW} -z max-page-size=0x1000 --whole-archive ${CMAKE_BINARY_DIR}/lib/lib${NACL_BOOTSTRAP_LIBRARY_NAME}.a --no-whole-archive
    DEPENDS ${NACL_BOOTSTRAP_LIBRARY_NAME}
)

add_custom_target(${NACL_HELPER_BOOTSTRAP} ALL
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/nacl_bootstrap_munge_phdr.py ${CMAKE_BINARY_DIR}/bin/${NACL_BOOTSTRAP_MUNGE_PHDR_NAME} ${CMAKE_BINARY_DIR}/bin/${NACL_BOOTSTRAP_RAW} ${CMAKE_BINARY_DIR}/bin/${NACL_HELPER_BOOTSTRAP}
    DEPENDS ${NACL_BOOTSTRAP_RAW} ${NACL_BOOTSTRAP_MUNGE_PHDR_NAME}
)
