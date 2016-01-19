set(PROJECT_UNIT_TESTS_DIR ${PROJECT_TESTS_DIR}/unit)

# Find gtest.
find_package(GTest REQUIRED)
include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})

macro(add_unit_test name file)
  string(CONCAT TESTS ${TESTS} ${name})
  add_executable(${name} EXCLUDE_FROM_ALL ${file})
  target_link_libraries(${name} ${GTEST_BOTH_LIBRARIES} pthread libnolimix86)
endmacro()

# Output all tests in build/tests/bin.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/tests/bin)

# Unit tests here.
add_unit_test(ast_test ast.cc)

# Call the script that runs the test.
add_custom_target(check-unit
  COMMAND ${PROJECT_UNIT_TESTS_DIR}/test.py ${PROJECT_BINARY_DIR}/tests/bin
  DEPENDS ${TESTS}
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)
