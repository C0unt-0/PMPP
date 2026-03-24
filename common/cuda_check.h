// Reusable CUDA error checking macro.
//
// Wraps any CUDA runtime API call and checks its cudaError_t return value.
// If the call fails, it prints the source file, line number, and a
// human-readable error description to stderr, then terminates the program.
//
// The do { ... } while (0) idiom ensures the macro behaves as a single
// statement, so it works safely in if/else blocks without braces.
//
// Usage:
//   CUDA_CHECK(cudaMalloc((void**)&d_ptr, size));
//   CUDA_CHECK(cudaMemcpy(d_ptr, h_ptr, size, cudaMemcpyHostToDevice));

#ifndef CUDA_CHECK_H
#define CUDA_CHECK_H

#include <stdio.h>   // fprintf, stderr
#include <stdlib.h>  // exit, EXIT_FAILURE

#define CUDA_CHECK(call)                                                       \
    do {                                                                       \
        cudaError_t err = (call);  /* execute the CUDA call and capture the    \
                                      error code */                            \
        if (err != cudaSuccess) {                                              \
            fprintf(stderr, "CUDA error at %s:%d - %s\n", __FILE__, __LINE__, \
                    cudaGetErrorString(err));  /* print file, line, and error   \
                                                 description */                \
            exit(EXIT_FAILURE);               /* abort on failure */            \
        }                                                                      \
    } while (0)

#endif
