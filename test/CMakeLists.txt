cmake_minimum_required(VERSION 3.10)

project(Generation3LCRNG)

set(CMAKE_C_STANDARD 11)

set(EXECUTABLE_NAME "bin")

get_filename_component(PARENT_DIR ../ ABSOLUTE)

include_directories(${PARENT_DIR}/include)

set(SRC_FILES ${PARENT_DIR}/test/main.c)

file(GLOB SRC_FILES_IN_SRC ${PARENT_DIR}/src/*.c)

set(ALL_SRC_FILES ${SRC_FILES} ${SRC_FILES_IN_SRC})

add_executable(${EXECUTABLE_NAME} ${ALL_SRC_FILES})

set(INIH_DIR ${PARENT_DIR}/external/inih)

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

add_library(inih STATIC ${PARENT_DIR}/external/inih/ini.c)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE inih)

target_include_directories(${EXECUTABLE_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/external/inih)