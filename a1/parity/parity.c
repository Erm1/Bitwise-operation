#include <stdio.h>
#include <stdint.h>
#include "parity.h"

#define MAX 8;
/* do not change function signatures */

/* Note this file uses binary notation 1001 1010 to indicate numbers
   in the comments. This notation is NOT supported by C, so don't type
   them in. Convert them to hexadecimal first, e.g. 0x9a */

/* count the number of 1 bits in x */
/* e.g. count_bits(0101) = 2 */
int count_bits(uint8_t x) {
    int mask;
    int count=0;
    for(int i = 7; i>=0; i--){
        mask = x>>i;
        if(mask & 1){
            count++;
            //printf("1");
        } 
    }
  return count;
}

/* return the value x if the number of 1 bits in x is even */
/* return the value x setting the 8th bit (counting from 1) to 1 if
   the number of 1 bits is odd */
/* e.g. #1:  x = (in binary) 0100 1000, then return value is 0100 1000 */
/*      #2:  x = (in binary) 0100 1001, then return value is 1100 1001 */

/* input x will always be a value 0 to 127 */
/* output value should always contain an even number of 1 bits */
uint8_t even_parity(uint8_t x) {
    
    if(count_bits(x)%2 == 0){
        return x;
    } else{
        return x+128;
    }
}

/* similar to even_parity, except that the number of 1 bits will always be odd */
/* e.g. #1:  x = (in binary) 0100 1000, then return value is 1100 1000 */
/*      #2:  x = (in binary) 0100 1001, then return value is 0100 1001 */
/* input x will always be a value 0 to 127 */
/* output value should always contain an odd number of 1 bits */
uint8_t odd_parity(uint8_t x) {
    if(count_bits(x)%2 != 0){
        return x;
    } else{
        return x+128;
    }
}


/* calculate the number of bit positions by which x and y differ */
/* e.g. x = (in binary) 1001 1001 */
/*      y = (in binary) 1101 0011 */
/* x and y differ in    SDSS DSDS  = 3 positions */
uint8_t hamming_distance(uint8_t x, uint8_t y) {
    int mask1;
    int mask2;
    int count=0;
    for(int i = 7; i>=0; i--){
        mask1 = x>>i;
        mask2 = y>>i;
        if((mask1 ^ mask2) & 1){
            count++;
            //printf("1");
        } else{
            //printf("0");
        }
    }
    return count;
}

