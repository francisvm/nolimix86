set(PROJECT_TESTS_DIR ${PROJECT_SOURCE_DIR}/tests)

add_subdirectory("suite")
add_subdirectory("unit")

add_custom_target(check
  DEPENDS check-functional
  DEPENDS check-unit
)
