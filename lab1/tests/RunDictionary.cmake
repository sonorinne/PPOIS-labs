execute_process(
  COMMAND "${PROGRAM}"
  INPUT_FILE "${CMAKE_CURRENT_LIST_DIR}/dictionary_utf8.txt"
  OUTPUT_VARIABLE output
  ERROR_VARIABLE errors
  RESULT_VARIABLE result
  TIMEOUT 5
)

if(NOT "${result}" STREQUAL "0")
  message(FATAL_ERROR "Dictionary failed: ${result}\n${output}\n${errors}")
endif()

foreach(translation IN ITEMS "яблоко" "голубое небо")
  if(NOT output MATCHES "${translation}")
    message(FATAL_ERROR "Missing UTF-8 translation: ${translation}\n${output}")
  endif()
endforeach()
