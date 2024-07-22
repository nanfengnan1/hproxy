#ifndef HLIB_H
#define HLIB_H

#define __hlib_packed __attribute__ ((packed))

#define HLIB_PACKED(x) x __attribute__ ((packed))
#define HLIB_UNUSED(x) x __attribute__ ((unused))

#define PREDICT_FALSE(x) __builtin_expect((x), 0)
#define PREDICT_TRUE(x) __builtin_expect((x), 1)

#define HLIB_COMPILER_BARRIER() asm volatile ("":::"memory")
 
#endif
