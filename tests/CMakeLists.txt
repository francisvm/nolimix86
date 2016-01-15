add_custom_target(check
  COMMAND ${PROJECT_SOURCE_DIR}/tests/test.py ${PROJECT_SOURCE_DIR}/tests/tests/good/
  DEPENDS nolimia32
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)
