set(nolimia32_src
  nolimia32.cc
  program.cc
)

set(llvm_components
  x86asmparser
)

add_executable(nolimia32 ${nolimia32_src})

# Link LLVM components
llvm_map_components_to_libnames(llvm_libs ${llvm_components})
target_link_libraries(nolimia32 ${llvm_libs})

message(STATUS "Found the following LLVM libraries:")
foreach(component ${llvm_components})
  message(STATUS "  ${component}")
endforeach()
