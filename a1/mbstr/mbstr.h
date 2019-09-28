/*
   Input mbstr is an array containing bytes, its length (in bytes) is nbytes.

   Compute and return the number of characters of the multibyte string.
 */
size_t mbstr_length(uint8_t mbstr[], size_t nbytes);

/*

  Encode characters from 0 to 1114111 (decimal) in mbstr. Assume mbstr
  is an array at least 4 bytes long.

  Return the number of bytes in the encoded value (1 to 4).

  Return 0 if c is outside the valid range of characters.

 */

int encode(uint32_t c, uint8_t mbstr[]);

/*

  Decode the character in mbstr, which is an array of 4 bytes
  (always).

  Return a 32-bit unsigned integer such that:

  bits 0--21 are the decoded character (0--1114111)

  bits 22--24 are the number of bytes decoded (0--4)

  Set bits 0--24 to zero if you encounter an incorrectly encoded
  character.

*/

uint32_t decode(uint8_t mbstr[]);

/* Convert the variable-length encoded mbstr to a fixed
   length string where each character occupies exactly 32-bits.

   You can assume the output array output_str contains at least nbytes
   elements.

   Return the actual number of characters decoded.

   Leave unchanged if not attempting.
 */
size_t mbstr_to_fixed(uint8_t mbstr[], size_t nbytes, uint32_t output_str[]);

