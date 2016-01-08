set(nolimia32_src
  nolimia32.cc
)

add_executable(nolimia32 ${nolimia32_src})
target_link_libraries(nolimia32 LLVMSupport)
target_link_libraries(nolimia32 rt dl curses pthread z m)
