cmake_minimum_required(VERSION 3.20)
project(PPOISLab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_COVERAGE "Collect coverage with GCC" OFF)
if(ENABLE_COVERAGE)
  if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(FATAL_ERROR "Coverage requires GCC")
  endif()
  add_compile_options(--coverage -O0 -g)
  add_link_options(--coverage)
endif()

if(MSVC)
  add_compile_options(/W4 /utf-8)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_library(lab1_core
  dictionary/Dictionary.cpp
  turing/Tape.cpp
  turing/Program.cpp
  turing/TuringMachine.cpp
)
target_include_directories(lab1_core PUBLIC dictionary turing)

add_library(lab1_menus cli/DictionaryMenu.cpp cli/TuringMenu.cpp)
target_link_libraries(lab1_menus PUBLIC lab1_core)
target_include_directories(lab1_menus PUBLIC cli)

add_executable(dictionary cli/dictionary_main.cpp)
target_link_libraries(dictionary PRIVATE lab1_menus)
add_executable(turing cli/turing_main.cpp)
target_link_libraries(turing PRIVATE lab1_menus)

install(TARGETS dictionary turing RUNTIME DESTINATION .)
install(DIRECTORY examples DESTINATION .)

include(CTest)
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

find_package(Doxygen QUIET)
if(Doxygen_FOUND)
  set(DOXYGEN_EXTRACT_ALL YES)
  set(DOXYGEN_GENERATE_LATEX NO)
  doxygen_add_docs(docs dictionary turing cli)
endif()
