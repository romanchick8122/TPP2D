add_executable(server main.cpp)
if(NOT UNIX)
    target_link_libraries(server PRIVATE ws2_32)
endif()