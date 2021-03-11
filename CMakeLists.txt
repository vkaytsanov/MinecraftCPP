cmake_minimum_required(VERSION 3.17)
project(Minecraft)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
        "src/desktop/*.cpp"
        "src/core/*.cpp"
        "src/core/include/*.h"
        "src/core/objects/*.cpp"
        "src/core/objects/include/*.h"
        "src/core/data/*.cpp"
        "src/core/data/include/*.h"
        "src/core/data/gameObjects/*.cpp"
        "src/core/data/gameObjects/include/*.h"
        "src/core/data/prefabs/*.cpp"
        "src/core/data/prefabs/include/*.h"
        "src/core/data/terrain/*.cpp"
        "src/core/data/terrain/include/*.h"
        "src/core/data/terrain/biomes/*.cpp"
        "src/core/data/terrain/biomes/include/*.h"
        "src/core/data/gameObjects/generic/*.cpp"
        "src/core/data/gameObjects/generic/include/*.h"
        "src/core/graphics/*.cpp"
        "src/core/graphics/include/*.h"
        "src/core/graphics/screens/*.cpp"
        "src/core/graphics/screens/include/*.h"
        "src/core/logic/*.cpp"
        "src/core/logic/include/*.h"
        "src/core/logic/events/*.cpp"
        "src/core/logic/events/include/*.h"
        "src/lib/*.cpp"
        "src/lib/include/*.h"
        "src/lib/entityx/*.h"
        "src/lib/entityx/*.cc"
        "src/lib/entityx/3rdparty/*.hpp"
        "src/lib/entityx/3rdparty/*.h"
        "src/lib/entityx/deps/*.h"
        "src/lib/entityx/help/*.h"
        "src/lib/entityx/help/*.cc"
        "src/lib/entityx/tags/*.h"
        "src/lib/entityx/tags/*.cc"
        "src/core/systems/*.cpp"
        "src/core/systems/include/*.h"
        "src/core/components/*.cpp"
        "src/core/components/include/*.h"
        "src/core/events/*.h"
        "src/lib/utils/camera/*.cpp"
        "src/lib/utils/camera/include/*.h"
        "src/lib/utils/geometry/*.cpp"
        "src/lib/utils/geometry/include/*.h"
        "src/lib/utils/math/*.cpp"
        "src/lib/utils/math/include/*.h"
        "src/lib/utils/noise/*.h"
        "src/lib/utils/noise/*.cpp"
        "src/lib/utils/noise/model/*.h"
        "src/lib/utils/noise/model/*.cpp"
        "src/lib/utils/noise/module/*.h"
        "src/lib/utils/noise/module/*.cpp"
        "src/lib/utils/openGL/*.cpp"
        "src/lib/utils/openGL/include/*.h"
        "src/lib/utils/ui/*.cpp"
        "src/lib/utils/ui/include/*.h"
        "src/lib/utils/*.cpp"
        "src/lib/utils/include/*.h"
        )
add_executable(${PROJECT_NAME} ${SOURCES})

# in case CMake doesn't find the libraries uncomment the following lines
# and put your path to the dependencies and add the cmake/sdl2-m_config.cmake
# file to the root of that directory

list(APPEND CMAKE_PREFIX_PATH "D:/SDL2")
list(APPEND CMAKE_PREFIX_PATH "D:/glew2")

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)


include_directories(${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2AUDIO_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
