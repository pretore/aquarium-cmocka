cmake_minimum_required(VERSION 3.22)
project(aquarium-cmocka VERSION 1.5.2
        LANGUAGES C
        DESCRIPTION "aquarium test harness")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
# Dependencies
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
find_package(Doxygen OPTIONAL_COMPONENTS dot mscgen dia)
include(cmake/FetchCMocka.cmake)

# Sources
set(EXPORTED_HEADER_FILES
        include/test/cmocka/pthread.h
        include/test/cmocka/stdlib.h
        include/test/cmocka/time.h
        include/test/cmocka.h)
set(SOURCES
        ${EXPORTED_HEADER_FILES}
        src/cmocka.c
        src/pthread.c
        src/stdlib.c
        src/time.c)

if (DOXYGEN_FOUND)
    set(DOXYGEN_EXTRACT_ALL YES)
    doxygen_add_docs(${PROJECT_NAME}-documentation
            ${EXPORTED_HEADER_FILES})
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    include(CTest)
    add_library(${PROJECT_NAME} STATIC "")
    add_compile_definitions(TEST)
    add_compile_definitions(_GNU_SOURCE)
    target_sources(${PROJECT_NAME}
            PRIVATE
                ${SOURCES})
    target_link_libraries(${PROJECT_NAME}
            PUBLIC
                ${CMAKE_THREAD_LIBS_INIT}
                cmocka::cmocka)
    target_include_directories(${PROJECT_NAME}
            PUBLIC
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>")
    # Unit Tests
    enable_testing()
    # aquarium-cmocka-unit-test
    add_executable(${PROJECT_NAME}-unit-test test/test_cmocka.c)
    target_include_directories(${PROJECT_NAME}-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-unit-test ${PROJECT_NAME}-unit-test)
    # aquarium-cmocka-stdlib-unit-test
    add_executable(${PROJECT_NAME}-stdlib-unit-test test/test_stdlib.c)
    target_include_directories(${PROJECT_NAME}-stdlib-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-stdlib-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-stdlib-unit-test ${PROJECT_NAME}-stdlib-unit-test)
    # aquarium-cmocka-pthread-unit-test
    add_executable(${PROJECT_NAME}-pthread-unit-test test/test_pthread.c)
    target_include_directories(${PROJECT_NAME}-pthread-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-pthread-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-pthread-unit-test
            ${PROJECT_NAME}-pthread-unit-test)
    # aquarium-cmocka-time-unit-test
    add_executable(${PROJECT_NAME}-time-unit-test test/test_time.c)
    target_include_directories(${PROJECT_NAME}-time-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-time-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-time-unit-test ${PROJECT_NAME}-time-unit-test)
endif ()
