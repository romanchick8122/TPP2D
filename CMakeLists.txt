cmake_minimum_required(VERSION 3.16)
project(TPP2D)
set(CMAKE_CXX_STANDARD 17)
include_directories(include)
include_directories(include/engine)
include_directories(include/GameLogic)

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

add_executable(TPP2D src/GameLogic/Cell.cpp src/GameLogic/SquadOrder.cpp include/GameLogic/SquadOrder.h src/GameLogic/Action.cpp include/GameLogic/Action.h src/GameLogic/Flag.cpp include/GameLogic/Flag.h src/GameLogic/AllFlags.cpp include/GameLogic/AllFlags.h src/GameLogic/Factory.cpp include/GameLogic/Factory.h src/GameLogic/AllUnits.cpp include/GameLogic/AllUnits.h src/GameLogic/SquadTemplate.cpp include/GameLogic/SquadTemplate.h)

#Adding submodules
if(NOT EXISTS delaunay-triangulation-algorithm/src/scanline_triangulation.cpp)
    message(Submodule not found)
    file(REMOVE delaunay-triangulation-algorithm)
    execute_process(COMMAND git submodule add --force https://github.com/pkositsyn/delaunay-triangulation-algorithm)
    execute_process(COMMAND git submodule update --force delaunay-triangulation-algorithm)
endif()
include_directories(delaunay-triangulation-algorithm/src)
target_sources(TPP2D PUBLIC
        delaunay-triangulation-algorithm/src/models.cpp
        delaunay-triangulation-algorithm/src/scanline_triangulation.cpp)

add_subdirectory(src)

get_target_property(sources TPP2D SOURCES)

#linking SFML
target_link_libraries(TPP2D PRIVATE sfml-graphics)
