project("simple ui")
cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")


include(FetchContent)

FetchContent_Declare(expected
  GIT_REPOSITORY https://github.com/TartanLlama/expected
  GIT_TAG        v1.1.0
  )

# make available
FetchContent_MakeAvailable(expected)

find_package(fmt)

add_library(fb fb.cpp guitext.cpp)
target_link_libraries(fb PUBLIC fmt::fmt-header-only)

target_link_libraries(fb PUBLIC expected)



add_executable(main main.cpp)
target_compile_options(main PRIVATE -static)
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} / "include")


target_link_libraries(main PRIVATE fb -static)