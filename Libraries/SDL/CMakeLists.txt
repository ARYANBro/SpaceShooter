cmake_minimum_required(VERSION 3.24.0)

project(SDL)

add_library(${PROJECT_NAME} INTERFACE)

file(GLOB_RECURSE Sources
	SDL2/include/**.h
	SDL2_image/include/*.h
	SDL2_mixer/include/*.h
	SDL2_ttf/include/*.h
)

target_sources(${PROJECT_NAME}
	PRIVATE ${Sources}
)

target_include_directories(${PROJECT_NAME}
	INTERFACE SDL2-2.0.22/include
	INTERFACE SDL2_image-2.6.1/include
	INTERFACE SDL2_mixer-2.6.1/include
	INTERFACE SDL2_ttf-2.20.0/include
)

target_link_directories(${PROJECT_NAME}
	INTERFACE SDL2-2.0.22/lib/x64
	INTERFACE SDL2_image-2.6.1/lib/x64
	INTERFACE SDL2_mixer-2.6.1/lib/x64
	INTERFACE SDL2_ttf-2.20.0/lib/x64
)

target_link_libraries(${PROJECT_NAME}
	INTERFACE SDL2main
	INTERFACE SDL2
	INTERFACE SDL2_image
	INTERFACE SDL2_mixer
	INTERFACE SDL2_ttf
)

install(
	FILES

	SDL2-2.0.22/lib/x64/SDL2.dll
	SDL2_image-2.6.1/lib/x64/SDL2_image.dll
	SDL2_mixer-2.6.1/lib/x64/SDL2_mixer.dll
	SDL2_ttf-2.20.0/lib/x64/SDL2_ttf.dll

	DESTINATION ${CMAKE_BINARY_DIR}/$<CONFIG>
)