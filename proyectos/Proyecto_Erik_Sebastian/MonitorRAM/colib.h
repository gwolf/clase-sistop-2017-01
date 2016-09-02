//Compiler overrides lib

#ifndef COLIB_H
#define COLIB_H

#define FORCEINLINE inline __attribute__ ((always_inline))
#define FORCENOINLINE __attribute__((noinline))

#endif // COLIB_H
