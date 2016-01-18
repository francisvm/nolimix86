add_subdirectory("suite")

add_custom_target(check
  DEPENDS check-functional
)
