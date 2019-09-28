#define _POSIX_C_SOURCE 200809
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "mbstr.h"

/* routines below should not be ordinarily modified */
void do_check(int test, const char *message) {
  fprintf(stderr, "%s: %s\n", message, test ? "SUCCESS" : "FAIL");
}

void decode_check(uint32_t value, uint32_t expected, const char *message, uint8_t line[]) {
  int i = 0;

  fprintf(stderr, "%s { 0x%x, 0x%x, 0x%x, 0x%x }, got value: 0x%x, expected 0x%x: %s\n",
		  message, line[0], line[1], line[2], line[3],
		  value, expected, (value == expected) ? "SUCCESS" : "FAIL");
}


void encode_check(uint8_t value[], uint8_t expected[], int nvalue, int nexpected,
				  const char *message) {
  int i = 0;
  int success = 1;

  fprintf(stderr, "%s, expecting nbytes %d, got %d\n", message, nexpected, nvalue);
  success = success & (nexpected  == nvalue);

  for(i = 0; i < nexpected; i++) {
	fprintf(stderr, "\tgot 0x%x expected 0x%x\n", value[i], expected[i]);
	success &= (value[i] == expected[i]);
  }

  fprintf(stderr, "\t%s: %s\n", message, success ? "SUCCESS" : "FAIL");
}


void check_decode() {
  uint8_t line[4];

  line[0] = 0x41;  line[1] = 0x42; line[2] = 0x43; line[3] = 0x44;
  decode_check(decode(line), 0x400041, "decoding", line);

  line[0] = 0xc2;  line[1] = 0x80; line[2] = 0x43; line[3] = 0x44;
  decode_check(decode(line), 0x800080, "decoding", line);

  line[0] = 0xf8;  line[1] = 0x41; line[2] = 0x43; line[3] = 0x44;
  decode_check(decode(line), 0, "decoding", line);

  line[0] = 0xc1;  line[1] = 0xc0; line[2] = 0x41; line[3] = 0x42;
  decode_check(decode(line), 0, "decoding", line);

  line[0] = 0xc0;  line[1] = 0x41; line[2] = 0x41; line[3] = 0x42;
  decode_check(decode(line), 0, "decoding", line);

  line[0] = 0xc0;  line[1] = 0x80; line[2] = 0x41; line[3] = 0x42;
  decode_check(decode(line), 0, "decoding", line);

  line[0] = 0xe0;  line[1] = 0xa0; line[2] = 0x80; line[3] = 0x42;
  decode_check(decode(line), 0xc00800, "decoding", line);

}


void check_encode() {
  uint8_t line[4];
  uint8_t expected[4];
  int n, nexpected;

  expected[0] = 0x41;
  nexpected = 1;
  n = encode(0x41, line);
  encode_check(line, expected, n, nexpected, "encoding 0x41");

  expected[0] = 0xc2;
  expected[1] = 0x80;
  nexpected = 2;
  n = encode(0x80, line);
  encode_check(line, expected, n, nexpected, "encoding 0x80");

  expected[0] = 0xe0;
  expected[1] = 0xa0;
  expected[2] = 0x80;
  nexpected = 3;
  n = encode(0x800, line);
  encode_check(line, expected, n, nexpected, "encoding 0x800");

  expected[0] = 0xf0;
  expected[1] = 0x90;
  expected[2] = 0x80;
  expected[3] = 0x80;
  nexpected = 4;
  n = encode(0x10000, line);
  encode_check(line, expected, n, nexpected, "encoding 0x10000");


  n = encode(1114112, line);
  encode_check(line, expected, n, 0, "encoding 114112");

}


void check_length(const char *filename) {
  FILE *f;
  uint8_t *line;
  size_t nbytes = 256;
  size_t nbytes_read = 0;
  int lineno = 0;

  line = malloc(sizeof(uint8_t) * nbytes);
  if(!line) {
	fprintf(stderr, "ERROR: Unable to allocate memory to store line.\n");
	exit(1);
  }

  f = fopen(filename, "r");
  if(!f) {
	fprintf(stderr, "ERROR: Unable to open '%s': %s.\n", filename, strerror(errno));
	exit(1);
  }

  while(!feof(f)) {
	if((nbytes_read = getline((char **) &line, &nbytes, f)) == -1) {
	  if(errno == 0)
		break; /* end-of-file */

	  fprintf(stderr, "ERROR: Unable to read line: %s.\n", strerror(errno));
	  exit(1);
	}
	lineno++;
	printf("%d: %zu bytes, %zu characters\n", lineno, nbytes_read, mbstr_length(line, nbytes_read));
  }

  fclose(f);

  free(line);
}

int main(int argc, char *argv[]) {
  if(argc != 2) {
	fprintf(stderr, "Usage: %s file\n", argv[0]);
	exit(1);
  }

  check_length(argv[1]);
  check_encode();
  check_decode();
}
