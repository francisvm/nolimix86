set(nolimix86_src
  # nolimix86
  nolimix86.cc
  asm-parser.cc
  streamer.cc

  # AST
  ast/instr.cc
)

set(llvm_components
  x86asmparser
)

add_executable(nolimix86 ${nolimix86_src})

# Link LLVM components
llvm_map_components_to_libnames(llvm_libs ${llvm_components})
target_link_libraries(nolimix86 ${llvm_libs})

message(STATUS "Found the following LLVM libraries:")
foreach(component ${llvm_components})
  message(STATUS "  ${component}")
endforeach()
