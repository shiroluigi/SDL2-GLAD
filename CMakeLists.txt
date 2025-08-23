cmake_minimum_required(VERSION 3.28.3)
project(guisdl)

add_executable(${PROJECT_NAME}
    ./src/main.cpp
    ./glad/src/gl.c
)

# Add include directories
target_include_directories(${PROJECT_NAME} PUBLIC
    ./headers
    ./glad/include
)

# Link SDL2 and dl
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2 dl)
