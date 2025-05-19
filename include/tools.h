#ifndef TOOLS_H
#define TOOLS_H

#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stddef.h>

typedef uint8_t   u8;
typedef int8_t    s8;
typedef uint16_t  u16;
typedef int16_t   s16;
typedef uint32_t  u32;
typedef int32_t   s32;
typedef uint64_t  u64;
typedef int64_t   s64;
typedef float     f32;
typedef double    f64;
typedef int32_t   b32;
typedef char      b8;

#ifdef TOOLS_DEFINE_NUMERIC_LIMITS
  static s8  S8_MIN  = (s8)0x80;
  static s16 S16_MIN = (s16)0x8000;
  static s32 S32_MN  = (s32)0x80000000;
  static s64 S64_MIN = (s64)0x8000000000000000llu;
  static s8  S8_MAX  = (s8) 0x7f;
  static s16 S16_MAX = (s16)0x7fff;
  static s32 S32_MAX = (s32)0x7fffffff;
  static s64 S64_MAX = (s64)0x7fffffffffffffffllu;
  static u8  U8_MAX  = 0xff;
  static u16 U16_MAX = 0xffff;
  static u32 U32_MAX = 0xffffffff;
  static u64 U64_MAX = 0xffffffffffffffffllu;
  static f64 F64_MAX = 1.7976931348623158e+308;
  static f64 F64_MIN_POS = 2.2250738585072014e-308;
  static f32 F32_MAX = 3.402823466e+38F;
  static f32 F32_MIN_POS = 1.175494351e-38F;
#endif

#ifdef TOOLS_DEFINE_HASHING
  static inline u64 djb2_hash(u8 *str) {
    if (!str) return 0;
    u64 hash = 5381;
    int c;
    while ((c = *str++))
      hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
  }
#endif


#ifdef TOOLS_DEFINE_DYN_ARRAY
#define DA_REALLOC(c,p,s) realloc(p,s)
#define DA_FREE(c,p)      free(p)
  typedef struct {
      size_t len;
      size_t cap;
  }da_header;
#define da_hdr(t)        ((da_header *) (t) - 1)
#define da_cap(a)        ((a) ? da_hdr(a)->cap : 0)
#define da_len(a)        ((a) ? da_hdr(a)->len : 0)
#define da_push(a,v)     (da_maybegrow(a,1), (a)[da_hdr(a)->len++] = (v))
#define da_pop(a)        (da_hdr(a)->len--, (a)[da_hdr(a)->len])
#define da_maybegrow(a,n)((!(a) || da_hdr(a)->len + (n) > da_hdr(a)->cap) ? (da_grow(a,n,0),0) : 0)
#define da_grow(a,b,c)   ((a) = da_growf((a), sizeof *(a), (b), (c)))
#define da_last(a)       ((a)[da_hdr(a)->len-1])
#define da_del(a,i)      da_deln(a,i,1)
#define da_deln(a,i,n)   (memmove(&(a)[i], &(a)[(i)+(n)], sizeof *(a) * (da_hdr(a)->len-(n)-(i))), da_hdr(a)->len -= (n))
#define da_delswap(a,i)  ((a)[i] = da_last(a), da_hdr(a)->len -= 1)
#define da_free(a)       ((void) ((a) ? DA_FREE(NULL,da_hdr(a)) : (void)0), (a)=NULL)
  static inline void *da_growf(void *a, size_t elemsize, size_t addlen, size_t min_cap){
    da_header temp={0}; // force debugging
    void *b;
    size_t min_len = da_len(a) + addlen;
    (void) sizeof(temp);
    if (min_len > min_cap)
      min_cap = min_len;
    if (min_cap <= da_cap(a))
      return a;
    if (min_cap < 2 * da_cap(a))
      min_cap = 2 * da_cap(a);
    else if (min_cap < 4)
      min_cap = 4;
    b = DA_REALLOC(NULL, (a) ? da_hdr(a) : 0, elemsize * min_cap + sizeof(da_header));
    b = (char *) b + sizeof(da_header);
    if (a == NULL) {
      da_hdr(b)->len = 0;
    }
    da_hdr(b)->cap = min_cap;
    return b;
  }
  inline void da_freef(void *a){
    DA_FREE(NULL, da_hdr(a));
  }
#endif

#endif
