#ifndef PCH_H
#define PCH_H

// std libs
#include <set>
#include <list>
#include <cstdio>
#include <typeindex>
#include <typeinfo>
#include <random>
#include <limits>
#include <vector>
#include <string>
#include <bitset>
#include <cassert>
#include <memory>
#include <sstream>
#include <fstream>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <filesystem>

// export api
#ifdef LAME_EXPORT
#ifdef _MSC_VER
#define LAME_API __declspec(dllexport)
#else
#define LAME_API __attribute__((visibility("default")))
#endif

#else
#ifdef _MSC_VER
#define LAME_API __declspec(dllimport)
#else
#define LAME_API
#endif
#endif

// free allocated memory and sets it to null pointer
#define LAME_DELETE(m) if (m != NULL) { delete (m); m = NULL; }

// logging macros
#if defined(_DEBUG)
#define LAME_LOG(level, message, ...) \
fprintf(stderr, "[%s] ", level); \
    fprintf(stderr, message, ##__VA_ARGS__); \
    fprintf(stderr, "\n");

#define LAME_WARNING(message, ...) JENGINE_LOG("warning", message, ##__VA_ARGS__)
#define LAME_ERROR(message, ...) JENGINE_LOG("error", message, ##__VA_ARGS__)
#define LAME_INFO(message, ...) JENGINE_LOG("info", message, ##__VA_ARGS__)
#else
#define LAME_INFO
#define LAME_ERROR
#define LAME_WARNING
#endif

#define INVALID_ID 0

namespace elementled{
using uuid64 = size_t;
LAME_API uuid64 generateUUID();
LAME_API std::string n_to_string( float x );
LAME_API int getRandomNumber(int min, int max);
}

#endif // PCH_H
