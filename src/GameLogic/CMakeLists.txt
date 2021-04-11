add_subdirectory(Units)
add_subdirectory(Squad)
target_sources(TPP2D PUBLIC
        Cell.cpp
        Squad/SquadOrder.cpp
        Squad/Action.cpp
        Flag.cpp
        AllFlags.cpp
        Squad/SquadTemplate.cpp
        Squad/Squad.cpp)