execute_process(COMMAND "${PROGRAM}"
  INPUT_FILE "${CMAKE_CURRENT_LIST_DIR}/scenario.txt"
  OUTPUT_VARIABLE output RESULT_VARIABLE result TIMEOUT 10)
if(NOT "${result}" STREQUAL "0")
  message(FATAL_ERROR "CLI failed: ${result}")
endif()
foreach(expected IN ITEMS "Paid, change: 100" "Baked" "Packed" "Delivered" "Published: 5")
  if(NOT output MATCHES "${expected}")
    message(FATAL_ERROR "Missing ${expected}: ${output}")
  endif()
endforeach()
