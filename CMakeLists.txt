cmake_minimum_required(VERSION 3.16)
project(TPP2D)
set(CMAKE_CXX_STANDARD 17)
include_directories(include)
include_directories(include/engine)
include_directories(include/GameLogic)
include_directories(include/GameLogic/Units)
include_directories(include/GameLogic/Squad)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#SFML installation
if(EXISTS ${PROJECT_SOURCE_DIR}/SFML)
    message("SFML already downloaded")
else()
    message("Checking compiler...")
    if (UNIX)
	message(Downloading SFML for Linux)
	file(DOWNLOAD
		    https://www.sfml-dev.org/files/SFML-2.5.1-linux-gcc-64-bit.tar.gz
		    ${PROJECT_SOURCE_DIR}/SFML.tar.gz)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
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
    if (UNIX)
        execute_process(COMMAND tar xzf ${PROJECT_SOURCE_DIR}/SFML.tar.gz --strip-components=1
		--directory ${PROJECT_SOURCE_DIR}/SFML)
    else()
        execute_process(COMMAND tar xzf ${PROJECT_SOURCE_DIR}/SFML.zip --strip-components=1
                --directory ${PROJECT_SOURCE_DIR}/SFML)
    endif()
    file(REMOVE ${PROJECT_SOURCE_DIR}/SFML.zip)
endif()
set(SFML_DIR ${PROJECT_SOURCE_DIR}/SFML/lib/cmake/SFML)
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
include_directories(${PROJECT_SOURCE_DIR}/SFML/include)

if (NOT EXISTS ${PROJECT_SOURCE_DIR}/nlohmann/json.hpp)
    message("Downloading json parser")
    file(DOWNLOAD
            https://github.com/nlohmann/json/releases/download/v3.9.1/json.hpp
            ${PROJECT_SOURCE_DIR}/nlohmann/json.hpp)
endif()
include_directories(${PROJECT_SOURCE_DIR})

add_executable(TPP2D src/graphics/FanFacade.cpp include/graphics/FanFacade.h)
add_subdirectory(resources)

configure_file(defaultConfig.json ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config.json COPYONLY)

#Adding submodules
if(NOT EXISTS delaunay-triangulation-algorithm/src/scanline_triangulation.cpp)
    message(Submodule not found)
    file(REMOVE delaunay-triangulation-algorithm)
    execute_process(COMMAND git submodule init)
    execute_process(COMMAND git submodule update --force)
endif()
include_directories(delaunay-triangulation-algorithm/src)
target_sources(TPP2D PUBLIC
        delaunay-triangulation-algorithm/src/models.cpp
        delaunay-triangulation-algorithm/src/scanline_triangulation.cpp)

add_subdirectory(src)

get_target_property(sources TPP2D SOURCES)

#linking SFML
target_link_libraries(TPP2D PRIVATE sfml-graphics)
#sockets
if(NOT UNIX)
    target_link_libraries(TPP2D PRIVATE ws2_32)
endif()

add_subdirectory(server)

add_dependencies(TPP2D server)
