cmake_minimum_required(VERSION 3.24.0)

project(SpaceShooter)

add_subdirectory(Libraries/SDL)

file(GLOB_RECURSE Sources
	Source/*.cpp
)

set(CMAKE_CXX_STANDARD 20)
set(CAMKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} ${Sources})

target_include_directories(${PROJECT_NAME}
	PRIVATE Source
)

target_link_libraries(${PROJECT_NAME}
	SDL
)

target_compile_definitions(${PROJECT_NAME}
	PRIVATE SDL_MAIN_HANDLED
)

install(DIRECTORY Assets/ DESTINATION ${CMAKE_BINARY_DIR}/$<CONFIG>/Assets)
