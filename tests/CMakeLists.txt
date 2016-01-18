set(CATEGORY good)
set(PROJECT_TESTS_DIR ${PROJECT_SOURCE_DIR}/tests)

add_custom_target(generate_tests
  COMMAND ${PROJECT_TESTS_DIR}/gen-test.py
  WORKING_DIRECTORY ${PROJECT_TESTS_DIR}/${CATEGORY}
)

add_custom_target(check
  COMMAND ${PROJECT_TESTS_DIR}/test.py ${PROJECT_TESTS_DIR}/${CATEGORY}
  DEPENDS generate_tests nolimix86
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)
