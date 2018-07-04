# cmake_minimum_required(VERSION <specify CMake version here>)
project(SnakeGame C)

set(CMAKE_C_STANDARD 99)

add_executable(SnakeGame main.c snakeBody.c snakeBody.h Bonus.c Bonus.h snakeInterface.c snakeInterface.h mainGame.c mainGame.h Frame.c Frame.h Point.c Point.h Obstacle.c Obstacle.h)

target_link_libraries(SnakeGame GL)
target_link_libraries(SnakeGame glut)