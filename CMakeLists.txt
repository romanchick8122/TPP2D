cmake_minimum_required(VERSION 3.17)
project(TPP2D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CSS_STANDARD_LIBRARIES}")

#SFML installation
if(EXISTS ${PROJECT_SOURCE_DIR}/SFML)
    message("SFML already downloaded")
else()
    message("Checking compiler...")
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message(Downloading SFML for GCC...)
        if (${CMAKE_SIZEOF_VOID_P} STREQUAL "4")
            file(DOWNLOAD
                    https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit.zip
                    ${PROJECT_SOURCE_DIR}/SFML.zip)
        else()
            file(DOWNLOAD
                    https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip
                    ${PROJECT_SOURCE_DIR}/SFML.zip)
        endif()
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        if (${CMAKE_SIZEOF_VOID_P} STREQUAL "4")
            file(DOWNLOAD
                    https://www.sfml-dev.org/files/SFML-2.5.1-windows-vc15-32-bit.zip
                    ${PROJECT_SOURCE_DIR}/SFML.zip)
        else()
            file(DOWNLOAD
                    https://www.sfml-dev.org/files/SFML-2.5.1-windows-vc15-64-bit.zip
                    ${PROJECT_SOURCE_DIR}/SFML.zip)
        endif()
    else()
        message(FATAL_ERROR Unsupported compiler)
    endif()
    file(MAKE_DIRECTORY SFML)
    execute_process(COMMAND tar xzf ${PROJECT_SOURCE_DIR}/SFML.zip --strip-components=1
            --directory ${PROJECT_SOURCE_DIR}/SFML)
    file(REMOVE ${PROJECT_SOURCE_DIR}/SFML.zip)
    if (WIN32)
        execute_process(COMMAND ren SFML-2.5.1 SFML)
    else()
        execute_process(COMMAND mv SFML-2.5.1 SFML)
    endif()
endif()
set(SFML_DIR ${PROJECT_SOURCE_DIR}/SFML/lib/cmake/SFML)
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
file(COPY ${PROJECT_SOURCE_DIR}/SFML/bin DESTINATION ${CMAKE_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/SFML/include)

include(include/CMakeLists.txt)
include(src/CMakeLists.txt)

add_executable(TPP2D ${sources})

#linking SFML#
target_link_libraries(TPP2D sfml-graphics)