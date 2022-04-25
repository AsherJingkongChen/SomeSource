/**
 * int (pointed type)
 * int* (pointer_1) (pointer to int)
 * int** (pointer_2) (pointer to pointer)
 */


#include <stdio.h>  // printf
#include <stdint.h> // uintxx_t
#include <stdlib.h> // malloc

int main() 
{
    const uint64_t BigLength    = 5;
    const uint64_t BigSize      = sizeof(int*);
    const uint64_t SmallLength  = 11;
    const uint64_t SmallSize    = sizeof(int);

    // pointer_2 = pointer_2;
  
    int** big = (int**) malloc(BigLength * BigSize); 

    for (uint32_t i = BigLength; i--;)
    {
        // pointer_1 = pointer_1;
      
        *(big + i) = (int*) malloc(SmallLength * SmallSize);
        
        for (int j = SmallLength; j--;)
        {
            // *(pointer_2 + n) = pointer_1; 
            // *(pointer_1 + n) = int;
          
            *(*(big + i) + j) = j * 3; 
        }
    }

    for (uint32_t i = 0; i < BigLength; i++)
    {
        for (uint32_t j = 0; j < SmallLength; j++)
        {
            // *(pointer_2 + n) = pointer_1; 
            // *(pointer_1 + n) = int;
          
            printf("%d ", *(*(big + i) + j));
        }
      
        // *(pointer_2 + n) = pointer_1 [heap allocated];
      
        free(*(big + i));
        printf("\n");
    }
  
    // pointer_2 [heap allocated]
  
    free(big);

    return 0;
}
