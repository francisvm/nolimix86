set(PROJECT_UNIT_TESTS_DIR ${PROJECT_TESTS_DIR}/unit)

# Find gtest in the local submodule.
set(GTEST_DIR ${PROJECT_UNIT_TESTS_DIR}/googletest)
set(GTEST_INCLUDE_DIRS ${GTEST_DIR}/include)
set(GTEST_BINARY_DIR ${GTEST_DIR}/build)
include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})
set(GTEST_LIBRARY ${GTEST_BINARY_DIR}/libgtest.a)
set(GTEST_MAIN_LIBRARY ${GTEST_BINARY_DIR}/libgtest_main.a)
set(GTEST_BOTH_LIBRARIES ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})
message(STATUS "Found GTest: " ${GTEST_LIBRARY})

macro(add_unit_test name file)
  set(TESTS ${TESTS} ${name})
  add_executable(${name} EXCLUDE_FROM_ALL ${file})
  target_link_libraries(${name} ${GTEST_BOTH_LIBRARIES} pthread nolimix86_core)
endmacro()

# Output all tests in build/tests/bin.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/tests/bin)

# Unit tests here.
add_unit_test(ast_test ast.cc)
add_unit_test(vm_test vm.cc)
add_unit_test(mmu_test mmu.cc)

# Call the script that runs the test.
add_custom_target(check-unit
  COMMAND ${PROJECT_UNIT_TESTS_DIR}/test.py ${PROJECT_BINARY_DIR}/tests/bin
  DEPENDS ${TESTS}
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)
