set(libnolimix86_src
  # Parser
  asm-parser.cc
  streamer.cc

  # AST
  ast/ast.cc
  ast/instr-base.cc
  ast/operand.cc
  ast/basic-block.cc
  ast/pretty-printer.cc

  # VM
  vm/cpu.cc
)

set(nolimix86_src
  # nolimix86
  nolimix86.cc
)

set(llvm_components
  x86asmparser
)

# Create a library, to be shared with different executables.
add_library(nolimix86_core ${libnolimix86_src})
set_target_properties(nolimix86_core PROPERTIES COMPILE_FLAGS "-fPIC")

# Link LLVM components
llvm_map_components_to_libnames(llvm_libs ${llvm_components})
target_link_libraries(nolimix86_core ${llvm_libs})

message(STATUS "Found the following LLVM libraries:")
foreach(component ${llvm_components})
  message(STATUS "  ${component}")
endforeach()

# Create the main executable.
add_executable(nolimix86 ${nolimix86_src})
target_link_libraries(nolimix86 nolimix86_core)

macro(add_sanitizer name full_name)
  string(TOUPPER ${name} UP_NAME)
  message(STATUS "Building ${UP_NAME}.")
  add_executable(nolimix86-${name} EXCLUDE_FROM_ALL ${nolimix86_src})
  target_link_libraries(nolimix86-${name} nolimix86_core)
  set_target_properties(nolimix86-${name}
    PROPERTIES COMPILE_FLAGS "-fsanitize=${full_name}"
               LINK_FLAGS "-fsanitize=${full_name}"
  )
endmacro()

if(NOLIMIX86_ASAN)
  add_sanitizer(asan address)
endif()

if(NOLIMIX86_MSAN)
  add_sanitizer(msan memory)
endif()

if(NOLIMIX86_UBSAN)
  add_sanitizer(ubsan undefined)
endif()

if(NOLIMIX86_LSAN)
  add_sanitizer(lsan leak)
endif()
