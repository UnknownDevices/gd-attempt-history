#pragma once

#include <cocos2d.h>
#include <MinHook.h>
#include <TlHelp32.h>
#include <gd.h>
#include <logger.hpp>

// pretty everything in cocos2d starts with CC, so there is a low chance of collisions
// it also makes using cocos a lot nicer imo
using namespace cocos2d;

typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int_fast8_t   i8_fast;
typedef int_fast16_t  i16_fast;
typedef int_fast32_t  i32_fast;
typedef int_fast64_t  i64_fast;
typedef uint_fast8_t  u8_fast;
typedef uint_fast16_t u16_fast;
typedef uint_fast32_t u32_fast;
typedef uint_fast64_t u64_fast;

typedef int_least8_t   i8_least;
typedef int_least16_t  i16_least;
typedef int_least32_t  i32_least;
typedef int_least64_t  i64_least;
typedef uint_least8_t  u8_least;
typedef uint_least16_t u16_least;
typedef uint_least32_t u32_least;
typedef uint_least64_t u64_least;
