include(FetchContent)
FetchContent_Declare(doctest
  URL https://codeload.github.com/doctest/doctest/tar.gz/refs/tags/v2.4.11
  URL_HASH SHA256=632ed2c05a7f53fa961381497bf8069093f0d6628c5f26286161fbd32a560186
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  SOURCE_SUBDIR single-header-only
)
FetchContent_MakeAvailable(doctest)

add_executable(lab1_tests DictionaryTests.cpp TuringTests.cpp MenuTests.cpp)
target_link_libraries(lab1_tests PRIVATE lab1_menus)
target_include_directories(lab1_tests SYSTEM PRIVATE "${doctest_SOURCE_DIR}")
foreach(example IN ITEMS dictionary.txt unary_increment.txt)
  configure_file("${PROJECT_SOURCE_DIR}/examples/${example}" "examples/${example}" COPYONLY)
endforeach()
add_test(NAME unit COMMAND lab1_tests)

add_test(NAME dictionary_cli COMMAND dictionary)
add_test(NAME turing_menu COMMAND turing)
add_test(NAME turing_file COMMAND turing "${PROJECT_SOURCE_DIR}/examples/unary_increment.txt")
add_test(NAME turing_log COMMAND turing "${PROJECT_SOURCE_DIR}/examples/unary_increment.txt" -log)
set_tests_properties(turing_file PROPERTIES PASS_REGULAR_EXPRESSION "State: halt, head: 3")
set_tests_properties(turing_log PROPERTIES PASS_REGULAR_EXPRESSION "State: start, head: 1")
add_test(NAME turing_usage COMMAND turing -log)
set_tests_properties(turing_usage PROPERTIES WILL_FAIL TRUE)
