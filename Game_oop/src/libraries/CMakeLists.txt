cmake_minimum_required(VERSION 3.22)
project(library)

set(COMMANDS_H 
    Command/Command.h   
    Command/ChangeDifficulty.h
    Command/ChangeFieldSize.h
    Command/ExitGame.h
    Command/MovePlayer.h
    Command/RestartGame.h
    Command/StartGame.h
    Command/GoMainMenu.h
    Command/LoggingFile.h
    Command/LoggingStream.h
)

set(COMMANDS_SRC
    Command/ChangeDifficulty.cpp
    Command/ChangeFieldSize.cpp
    Command/ExitGame.cpp
    Command/MovePlayer.cpp
    Command/RestartGame.cpp
    Command/StartGame.cpp
    Command/GoMainMenu.cpp
    Command/LoggingFile.cpp
    Command/LoggingStream.cpp
)

set(STATES_H
    Game/State/GameState.h
    Game/State/LoseState.h
    Game/State/MainMenuState.h
    Game/State/PlayingState.h
    Game/State/WinState.h
    Game/State/EndState.h
)

set(STATES_SRC
    Game/State/LoseState.cpp
    Game/State/MainMenuState.cpp
    Game/State/PlayingState.cpp
    Game/State/WinState.cpp
    Game/State/EndState.cpp
)

set(MESSAGES_H
    Messages/MessageInterface.h
    Messages/Defines.h
    Messages/WinMessage.h
    Messages/LoseMessage.h
    Messages/NewGameMessage.h
    Messages/CorrectCommandMessage.h
    Messages/WrongCommandMessage.h
)

set(MESSAGES_SRC
    Messages/MessageInterface.cpp
    Messages/WinMessage.cpp
    Messages/LoseMessage.cpp
    Messages/NewGameMessage.cpp
    Messages/CorrectCommandMessage.cpp
    Messages/WrongCommandMessage.cpp
)

set(ENEMIES_H
    Enemies/Controls/Finding.h
    Enemies/Controls/Wandering.h
    Enemies/Interactions/Bounty.h
    Enemies/Interactions/DealDamage.h
    Enemies/Enemy.h
    Enemies/EnemyDefines.h
    Enemies/EnemyBase.h
    Enemies/EnemyDerived.h
)   

set(ENEMIES_SRC
    Enemies/Controls/Finding.cpp
    Enemies/Controls/Wandering.cpp
    Enemies/Interactions/Bounty.cpp
    Enemies/Interactions/DealDamage.cpp
)   

set(SOURCES 
    Player/Player.cpp
    Handlers/PlayerHandler.cpp
    World/Cell.cpp
    World/Field.cpp
    Event/MovementEvents/Teleport.cpp
    Event/NegativeEvents/Trap.cpp
    Event/PositiveEvents/MedKit.cpp
    FieldGenerator/RandomGenerator/Generator.cpp
    FieldGenerator/DefaultLevels/DefaultLevelGenerator.cpp
    ${COMMANDS_SRC}
    ${STATES_SRC}
    Game/Engine/GameEngine.cpp
    Input/FileInput.cpp
    Input/StreamInput.cpp
    Rendering/StreamRendering.cpp
    Rendering/FileRendering.cpp
    Tracking/Tracking.cpp
    ${MESSAGES_SRC}
    Logger/FileLogger.cpp
    Logger/Logger.cpp
    Logger/StreamLogger.cpp
    ${ENEMIES_SRC}
)

set(HEADERS 
    Player/Player.h
    Handlers/PlayerHandler.h
    World/Cell.h
    World/Field.h
    Point/Point.h
    Event/Interface/EventInterface.h
    Event/MovementEvents/Teleport.h
    Event/NegativeEvents/Trap.h
    Event/PositiveEvents/MedKit.h
    FieldGenerator/RandomGenerator/Generator.h
    FieldGenerator/DefaultLevels/DefaultLevelGenerator.h
    ${COMMANDS_H}
    ${STATES_H}
    Game/Engine/GameEngine.h
    Input/Defines.h
    Input/InputInterface.h
    Input/FileInput.h
    Input/StreamInput.h
    Rendering/RenderingInterface.h
    Rendering/StreamRendering.h
    Rendering/FileRendering.h
    Tracking/Tracking.h
    ${MESSAGES_H}
    Logger/FileLogger.h
    Logger/Logger.h
    Logger/StreamLogger.h
    Logger/LoggerInterface.h
    ${ENEMIES_H}
)

add_library(lib SHARED ${SOURCES} ${HEADERS})
target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})