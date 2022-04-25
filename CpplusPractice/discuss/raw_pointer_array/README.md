```rust
==37102== Memcheck, a memory error detector
==37102== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==37102== Using Valgrind-3.19.0.GIT-lbmacos and LibVEX; rerun with -h for copyright info
==37102== Command: ./simple_2d_raw_ptr_array
==37102== 
0 3 6 9 12 15 18 21 24 27 30 
0 3 6 9 12 15 18 21 24 27 30 
0 3 6 9 12 15 18 21 24 27 30 
0 3 6 9 12 15 18 21 24 27 30 
0 3 6 9 12 15 18 21 24 27 30 
==37102== 
==37102== HEAP SUMMARY:
==37102==     in use at exit: 17,911 bytes in 159 blocks
==37102==   total heap usage: 179 allocs, 20 frees, 22,915 bytes allocated
==37102== 
==37102== LEAK SUMMARY:
==37102==    definitely lost: 0 bytes in 0 blocks
==37102==    indirectly lost: 0 bytes in 0 blocks
==37102==      possibly lost: 0 bytes in 0 blocks
==37102==    still reachable: 2,048 bytes in 1 blocks
==37102==         suppressed: 15,863 bytes in 158 blocks
==37102== Reachable blocks (those to which a pointer was found) are not shown.
==37102== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==37102== 
==37102== For lists of detected and suppressed errors, rerun with: -s
==37102== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 4 from 4)
```
```h
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main() 
{
    const uint64_t BigLength    = 5;
    const uint64_t BigSize      = sizeof(int*);
    const uint64_t SmallLength  = 11;
    const uint64_t SmallSize    = sizeof(int);

    int** big = (int**) malloc(BigLength * BigSize);

    for (uint32_t i = BigLength; i--;)
    {
        *(big + i) = (int*) malloc(SmallLength * SmallSize);
        for (int j = SmallLength; j--;)
        {
            *(*(big + i) + j) = j * 3;
        }
    }

    for (uint32_t i = 0; i < BigLength; i++)
    {
        for (uint32_t j = 0; j < SmallLength; j++)
        {
            printf("%d ", *(*(big + i) + j));
        }
        free(*(big + i));
        printf("\n");
    }
    free(big);

    return 0;
}
```
