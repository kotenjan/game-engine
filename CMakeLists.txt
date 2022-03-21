cmake_minimum_required(VERSION 3.16)
project(Game)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED SDL2)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

set(SOURCE_FILES Init/main.cpp Init/Game.cpp Init/Game.h Graphics/Texture.cpp Graphics/Texture.h Objects/Entity.cpp Objects/Entity.h Objects/Map.cpp Objects/Map.h Objects/Tile.cpp Objects/Tile.h Objects/Position.cpp Objects/Position.h Graphics/Databank.cpp Graphics/Databank.h Objects/Objects.cpp Objects/Objects.h Objects/Player.cpp Objects/Player.h Objects/Pirate.cpp Objects/Pirate.h Objects/Element.cpp Objects/Element.h Objects/GameStart.cpp Objects/GameStart.h Objects/HealthBar.cpp Objects/HealthBar.h Objects/Stats.cpp Objects/Stats.h Objects/StaminaBar.cpp Objects/StaminaBar.h Objects/Inventory.cpp Objects/Inventory.h Objects/ContinueButton.cpp Objects/ContinueButton.h Objects/Key.cpp Objects/Key.h Objects/Heart.cpp Objects/Heart.h Objects/Sword.cpp Objects/Sword.h Objects/Gun.cpp Objects/Gun.h Objects/Bullet.cpp Objects/Bullet.h Objects/PlayerIcon.cpp Objects/PlayerIcon.h Objects/TextBox.cpp Objects/TextBox.h Objects/UnlockedTile.cpp Objects/UnlockedTile.h Init/Controller.cpp Init/Controller.h)
add_executable(Game Init/main.cpp Init/Game.cpp Init/Game.h Graphics/Texture.cpp Graphics/Texture.h Objects/Entity.cpp Objects/Entity.h Objects/Map.cpp Objects/Map.h Objects/Tile.cpp Objects/Tile.h Objects/Position.cpp Objects/Position.h Graphics/Databank.cpp Graphics/Databank.h Objects/Objects.cpp Objects/Objects.h Objects/Player.cpp Objects/Player.h Objects/Pirate.cpp Objects/Pirate.h Objects/Element.cpp Objects/Element.h Objects/GameStart.cpp Objects/GameStart.h Objects/HealthBar.cpp Objects/HealthBar.h Objects/Stats.cpp Objects/Stats.h Objects/StaminaBar.cpp Objects/StaminaBar.h Objects/Inventory.cpp Objects/Inventory.h Objects/ContinueButton.cpp Objects/ContinueButton.h Objects/Key.cpp Objects/Key.h Objects/Heart.cpp Objects/Heart.h Objects/Sword.cpp Objects/Sword.h Objects/Gun.cpp Objects/Gun.h Objects/Bullet.cpp Objects/Bullet.h Objects/PlayerIcon.cpp Objects/PlayerIcon.h Objects/TextBox.cpp Objects/TextBox.h Objects/UnlockedTile.cpp Objects/UnlockedTile.h Init/Controller.cpp Init/Controller.h)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} )

add_executable(SDL2_App ${SOURCE_FILES})


