#ifndef TYPE_H
#define TYPE_H
#include <stddef.h>
#include <stdint.h>

typedef size_t usize;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef __uint128_t u128;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef __int128_t i128;

typedef uint_least8_t uleast8;
typedef uint_least16_t uleast16;
typedef uint_least32_t uleast32;
typedef uint_least64_t uleast64;

typedef int_least8_t least8;
typedef int_least16_t least16;
typedef int_least32_t least32;
typedef int_least64_t least64;

typedef uint_fast8_t ufast8;
typedef uint_fast16_t ufast16;
typedef uint_fast32_t ufast32;
typedef uint_fast64_t ufast64;

typedef int_fast8_t fast8;
typedef int_fast16_t fast16;
typedef int_fast32_t fast32;
typedef int_fast64_t fast64;

typedef intmax_t imax;
typedef intptr_t iptr;

typedef long il;
typedef long long ill;
typedef unsigned long ul;
typedef unsigned long long ull;

typedef float f32;
typedef double f64;

typedef uint64_t v2u64 __attribute__((vector_size(16)));
typedef uint32_t v4u32 __attribute__((vector_size(16)));
typedef uint16_t v8u16 __attribute__((vector_size(16)));
typedef uint8_t v16u8 __attribute__((vector_size(16)));

#endif // TYPE_H
