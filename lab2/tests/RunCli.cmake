execute_process(COMMAND "${PROGRAM}"
  INPUT_FILE "${CMAKE_CURRENT_LIST_DIR}/scenario.txt"
  OUTPUT_VARIABLE output RESULT_VARIABLE result TIMEOUT 10 ENCODING UTF-8)
if(NOT "${result}" STREQUAL "0")
  message(FATAL_ERROR "CLI failed: ${result}")
endif()
foreach(expected IN ITEMS "Paid, change: 5[.]01 BYN" "Classic 29[.]99 BYN" "Pizzeria, total: 29[.]99 BYN" "Baked" "Packed" "Delivered" "Published: 5")
  if(NOT output MATCHES "${expected}")
    message(FATAL_ERROR "Missing ${expected}: ${output}")
  endif()
endforeach()
