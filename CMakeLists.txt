include(cmake/utils.cmake)
if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)
project(sylar)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CMAKE_CXX_FLAGS} -O0 -fPIC -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations -fPIC -pthread")
set(CMAKE_C_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -fPIC -ggdb -std=c11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")
include_directories(.)
option(BUILD_TEST "ON for complile test" OFF)
find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

force_redefine_file_macro_for_sources(sylar)

set(LIB_SRC
    sylar/config.cpp
    sylar/fiber.cpp
    sylar/log.cpp
    sylar/scheduler.cpp
    sylar/thread.cpp
    sylar/util.cpp
    )
add_library(sylar SHARED ${LIB_SRC})
# force_redefine_file_macro_for_sources(LIB_SRC)


find_library(YAMLCPP yaml-cpp)
find_library(PTHREAD pthread)
set(LIBS
    pthread
    sylar
    yaml-cpp
)

add_executable(test tests/test.cpp)
add_dependencies(test sylar)
force_redefine_file_macro_for_sources(test)
target_link_libraries(test ${LIBS})

add_executable(test_config tests/test_config.cpp sylar)
add_dependencies(test_config sylar)
force_redefine_file_macro_for_sources(test_config)
target_link_libraries(test_config ${LIBS})

add_executable(test_thread tests/test_thread.cpp sylar)
add_dependencies(test_thread sylar)
force_redefine_file_macro_for_sources(test_thread)
target_link_libraries(test_thread ${LIBS})

add_executable(test_util tests/test_util.cpp sylar)
add_dependencies(test_util sylar)
force_redefine_file_macro_for_sources(test_util)
target_link_libraries(test_util ${LIBS})

add_executable(test_fiber tests/test_fiber.cpp sylar)
add_dependencies(test_fiber sylar)
force_redefine_file_macro_for_sources(test_fiber)
target_link_libraries(test_fiber ${LIBS})

add_executable(test_scheduler tests/test_scheduler.cpp sylar)
add_dependencies(test_scheduler sylar)
force_redefine_file_macro_for_sources(test_scheduler)
target_link_libraries(test_scheduler ${LIBS})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
