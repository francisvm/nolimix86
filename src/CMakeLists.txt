set(libnolimix86_src
  # Parser
  asm-parser.cc
  streamer.cc

  # AST
  ast/ast.cc
  ast/instr-base.cc
  ast/operand.cc
  ast/ast.cc
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
