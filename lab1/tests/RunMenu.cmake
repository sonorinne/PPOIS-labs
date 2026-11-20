execute_process(
  COMMAND "${PROGRAM}"
  INPUT_FILE "${CMAKE_CURRENT_LIST_DIR}/menu_exit.txt"
  OUTPUT_VARIABLE output
  ERROR_VARIABLE errors
  RESULT_VARIABLE result
  TIMEOUT 5
)

if(NOT "${result}" STREQUAL "0")
  message(FATAL_ERROR "Menu failed: ${result}\n${output}\n${errors}")
endif()

if(NOT output MATCHES "${MENU_TITLE}")
  message(FATAL_ERROR "Expected menu title was not printed: ${output}")
endif()

message(STATUS "${MENU_TITLE}: started and exited successfully")
