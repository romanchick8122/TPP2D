add_subdirectory(actions)
add_subdirectory(GUI)
target_sources(TPP2D PUBLIC
        Action.cpp
        config.cpp
        gameController.cpp
        gameObject.cpp
        Logger.cpp
        NetworkManager.cpp
        gameplayClickableGameObject.cpp)