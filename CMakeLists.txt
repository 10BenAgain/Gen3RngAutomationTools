cmake_minimum_required(VERSION 3.10)

project(Generation3LCRNG)

set(CMAKE_C_STANDARD 11)

 set(EXECUTABLE_NAME "gts")

option(USE_BUILD_PATH "Use build path for encslot reads" OFF)

option(EXPANDED_PRINT "CLI 'pretty' print for search results" ON)

if (EXPANDED_PRINT)
    add_compile_definitions(EXPANDED_PRINT)
endif()

if(USE_BUILD_PATH)
    add_compile_definitions(BUILD_PATH)
endif()

add_compile_options(-O3)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SRC_FILES ${PROJECT_SOURCE_DIR}/main.c)

file(GLOB SRC_FILES_IN_SRC ${PROJECT_SOURCE_DIR}/src/*.c)

set(ALL_SRC_FILES ${SRC_FILES} ${SRC_FILES_IN_SRC})

add_executable(${EXECUTABLE_NAME} ${ALL_SRC_FILES})

set(INIH_DIR ${PROJECT_SOURCE_DIR}/external/inih)

if(NOT EXISTS ${INIH_DIR})
    message(STATUS "inih directory not found. Cloning into ${INIG_DIR}..")
    execute_process(
            COMMAND git clone https://github.com/benhoyt/inih.git ${INIH_DIR}
            RESULT_VARIABLE GIT_CLONE_RESULT
    )
    if (NOT GIT_CLONE_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone inih repository!")
    endif ()
endif ()

add_library(inih STATIC ${PROJECT_SOURCE_DIR}/external/inih/ini.c)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE inih)

target_include_directories(${EXECUTABLE_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/external/inih)