#include <stdio.h>
#include <stdint.h>
#include "parity.h"

void do_check(int test, const char *message) {
  fprintf(stderr, "%s: %s\n", message, test ? "SUCCESS" : "FAIL");
}


/*
 This is a simple test harness. modify it as you see fit. It is only
 valid when the functions in parity.c return a value. If the functions
 are empty, then the tests will be meaningless.

 Note that we will use a far more sophisticated test harness to verify
 your code.
 */
int main(void) {
  do_check(count_bits(129) == 2, "count_bits test #1");
  do_check(count_bits(0) == 0, "count_bits test #2");
  do_check(count_bits(1) == 1, "count_bits test #3");
  do_check(even_parity(0x48) == 0x48, "even_parity test #1");
  do_check(even_parity(0x45) == 0xc5, "even_parity test #2");
  do_check(odd_parity(0x48) == 0xc8, "odd_parity test #1");
  do_check(odd_parity(0x45) == 0x45, "odd_parity test #2");
  do_check(hamming_distance(0xc5, 0xd3) == 3, "hamming_distance test");

  return 0;
}
