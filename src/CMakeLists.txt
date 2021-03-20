add_subdirectory(util)
add_subdirectory(engine)
add_subdirectory(graphics)
target_sources(TPP2D PUBLIC
        main.cpp
        GameLogic/UnitOrder.cpp
        GameLogic/Unit.cpp
        GameLogic/Squad.cpp)
