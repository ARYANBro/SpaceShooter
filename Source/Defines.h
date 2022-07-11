#pragma once

#include <cassert>

#define CHECK_SDL_ERROR_FUNC(trueCond, getError)		\
if (!(trueCond))										\
{														\
	using namespace std::string_literals;				\
	std::string error = "SDL ERROR: "s + (getError)();  \
	assert(false && error.c_str());						\
}														\

#define CHECK_SDL_ERROR(trueCond) CHECK_SDL_ERROR_FUNC(trueCond, SDL_GetError)
#define CHECK_SDL_IMAGE_ERROR(trueCond) CHECK_SDL_ERROR_FUNC(trueCond, IMG_GetError)
#define CHECK_SDL_MIXER_ERROR(trueCond) CHECK_SDL_ERROR_FUNC(trueCond, Mix_GetError)
#define CHECK_SDL_TTF_ERROR(trueCond) CHECK_SDL_ERROR_FUNC(trueCond, TTF_GetError)