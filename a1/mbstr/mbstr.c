#include <stdio.h>
#include <stdint.h>


uint8_t numofOnes(uint8_t num);


/*
   Multibyte encodings.

   In ASCII, a standard for encoding mostly English text data, each
   character (e.g. A to Z) occupies one byte. However, using one byte
   per character does not work for languages which may have a large
   number of characters.

   Such languages use a multibyte encoding where one character can
   occupy more than one byte. Many such multibyte encodings exist. One
   such encoding for a hypothetical language is described below:

   Assume that there are 1114112 characters of this language, so we
   can use 21 bits (so characters range from 0 to 1114111).

   Then,

   For values from 0 to 127 (which take 7 bits), the encoding is:

   0xxx xxxx - where the xxx xxxx bit indicate the character.

   e.g. 65 (0100 0001) => 0100 0001

   Thus, values from 0 to 127 consume only one byte.


   For values from 128 to 2047 (which take 11 bits), use two bytes:

   110x xxxx  10xx xxxx

   e.g. 128 (000 1000 0000) => 1100 0010 1000 0000
                                      ^^   ^^ ^^^^

   For values from 2048 to 65535 (which take 16 bits), use three bytes

   1110 xxxx  10xx xxxx  10xx xxxx


   For values from 65535 to 1114111 (which take 21 bits), use four bytes

   1111 0xxx  10xx xxxx  10xx xxxx  10xx xxxx

   This is a variable-length multibyte encoding, where each character
   can occupy 1 to 4 bytes.  In such encodings, a one-to-one relation
   between a character and a byte does not exist. Functions that
   operate on multibyte strings have to be rewritten.

   In this assignment, you will write functions to encode, decode, and
   find the length of strings.
*/



/*
   Input mbstr is an array containing bytes, its length (in bytes) is nbytes.

   Compute and return the number of characters of the multibyte string.
 */
size_t mbstr_length(uint8_t mbstr[], size_t nbytes) {
    
  /*
	 Note that in the encoding above, a character starts when the byte
	 contains a 0 bit in the 8th position (counting from 1), or if the
	 byte contains two or more high bits that are 1 followed by a 0.

	 Bytes that have one high bit that is one followed by a zero
	 (i.e. 10xx xxxx) are actually "inside" a multibyte character.
  */


  /* One strategy is to look at each byte, identify if it is the start of
	 a character, and increase the length if so. */

  /* WRITE YOUR CODE HERE */
    
    
    //        }
    //        int mask;
    //        int mask2;
    //        //        for(int j = 7; j>=0; j--){
    //        mask = mbstr[i]>>6;
    //        mask2 = mask>>1;
    //        if(mask == 2){
    //            continue;
    //        } else {
    //            length ++;
    //        }
    
    
    
    int length = 0;
    for(int i=0; i<nbytes; i++){
        
        //        int mask;
        //        int mask2;
        //        //        for(int j = 7; j>=0; j--){
        //        mask = mbstr[i]>>6;
        //        mask2 = mask>>1;
        //        if(mask == 2){
        //            continue;
        //        } else {
        //            length ++;
        //        }
        
        int mask;
        int mask2;
//        for(int j = 7; j>=0; j--){
            mask = mbstr[i]>>6;
            mask2 = mask>>1;
            if(mask&1){
                mask = mask>>1;
                if(mask&1){
                    length ++;
                }
            } else if((mask2&1) != 1){
                length ++;
            }
    }


    return length; /* change this to return the actual length*/

}



/*
 
 Encode characters from 0 to 1114111 (decimal) in mbstr. Assume mbstr
 is an array at least 4 bytes long.
 
 Return the number of bytes in the encoded value (1 to 4).
 
 Return 0 if c is outside the valid range of characters.
 
 */

int encode(uint32_t c, uint8_t mbstr[]) {
    
    int referenceByte = 0x80;
    int firstByte;
    
    if(c<=127){
        mbstr[0] = c;
        return 1;
    }
    if(c<=2047){

        for(int i=0; i<6;i++){
            int mask = c&0x1;
            referenceByte = referenceByte | (mask << i);
            c = c >> 1;
        }
        mbstr[1] = referenceByte;
        firstByte = 0xc0;
        
        for(int i=0; i<5;i++){
            int mask =  c&0x1;
            firstByte = firstByte | (mask << i);
            c = c >> 1;
        }
        mbstr[0] = firstByte;
        
        return 2;
    }
    if(c<=65535){
        
        for(int i=0; i<6;i++){
            int mask = c&0x1;
            referenceByte = referenceByte | (mask << i);
            c = c >> 1;
        }
        mbstr[2] = referenceByte;
        
        for(int i=0; i<6;i++){
            int mask = c&0x1;
            referenceByte = referenceByte | (mask << i);
            c = c >> 1;
        }
        mbstr[1] = referenceByte;
        
        firstByte = 0xE0;
        
        for(int i=0; i<4;i++){
            int mask =  c&0x1;
            firstByte = firstByte | (mask << i);
            c = c >> 1;
        }
        mbstr[0] = firstByte;
        
        return 3;
    }
    if(c<=1114111){
        
        for(int i=0; i<6;i++){
            int mask = c&0x1;
            referenceByte = referenceByte | (mask << i);
            c = c >> 1;
        }
        mbstr[3] = referenceByte;
        
        for(int i=0; i<6;i++){
            int mask = c&0x1;
            referenceByte = referenceByte | (mask << i);
            c = c >> 1;
        }
        mbstr[2] = referenceByte;
        
        for(int i=0; i<6;i++){
            int mask = c&0x1;
            referenceByte = referenceByte | (mask << i);
            c = c >> 1;
        }
        mbstr[1] = referenceByte;
        
        firstByte = 0xF0;
        
        for(int i=0; i<3;i++){
            int mask =  c&0x1;
            firstByte = firstByte | (mask << i);
            c = c >> 1;
        }
        mbstr[0] = firstByte;
        
        return 4;
    }
    
     else{
         return 0;
    }
    
    
    
//    BINARY               HEX
//    0100 0000            0x40
//    1100 0000            0xC0
//    1110 0000            0xE0
//    1111 0000            0xF0
    
}



/*
 
 Decode the character in mbstr, which is an array of 4 bytes
 (always).
 
 Return a 32-bit unsigned integer such that:
 
 bits 0--21 are the decoded character (0--1114111)
 
 bits 22--24 are the number of bytes decoded (0--4)
 
 Set bits 0--24 to zero if you encounter an incorrectly encoded
 character.
 
 Examples:
 
 #1:
 
 mbstr = {0x41, 0x42, 0x43, 0x44}
 
 return value should be (binary)
 0000 0000 0100 0000 0000 0000 0100 0001
 
 (i.e. 0x400041)
 
 (the only value decoded was 0x41 which occupies one byte)
 
 #2:
 
 mbstr = {0xc1, 0x80, 0x41, 0x42}
 
 return value should be (binary):
 0000 0000 1000 0000 0000 0000 1000 0000
 
 (i.e. 0x80080)
 
 (the value decoded was 0x80 which occupies two bytes)
 
 
 #3:
 
 mbstr = {0xf8, ?, ?, ?}  // ? indicates values are unimportant
 
 Note: 0xf8 is 1111 1000 which is not a valid encoding.
 
 Return 0
 
 
 #4:
 
 mbstr = {0xc1, 0xc0, 0x41, 0x42}
 
 Note: 0xc0 (1100 0000) cannot follow 0xc1 (1100 0001), so this is an
 invalid encoding.
 
 Return 0.
 
 #5:
 
 mbstr = {0xc0, 0x41, 0x41, 0x42}
 
 Note: 0xc0 (1100 0000) cannot start a character, so this is an also
 an invalid encoding.
 
 */

uint32_t decode(uint8_t mbstr[]) {
   
    if (mbstr[0] == 0xc0) {
        return 0x0;
    }
    
    uint32_t numBytes = mbstr[0] & 0xF0;
    
    if (numBytes == 0x40) {
        uint32_t result = mbstr[0];
        result |= 0x400000;
        return result;
    }
    
    if (numBytes == 0xC0) {
        uint32_t result = 0;
        
        int bits = mbstr[0] ^ 0xC0;
        result |= bits;
        bits = mbstr[1] & 0xC0;
        if (bits == 0xC0 || bits >> 7 != 1) {
            return 0;
        }
        
        bits = mbstr[1] ^ 0x80;
        
        result <<= 6;
        
        result |= bits;
       
        result |= 0x800000;
        return result;
    }
  
    if (numBytes == 0xE0) {
        uint32_t result = 0;
        
        int bits = mbstr[0] ^ 0xE0;
        result |= bits;
        
        for (int i = 1; i <= 2; i++) {
            bits = mbstr[i] & 0xC0;
            
            if (bits == 0xC0 || bits >> 7 != 1) {
                return 0;
            }
            
            bits = mbstr[i] ^ 0x80;
            result <<= 6;
            result |= bits;
        }
        
        result |= 0xC00000;
        
        return result;
    }
    
    if (numBytes == 0xF0) {
        uint32_t result = 0;
        int bits = mbstr[0] ^ 0xF0; // removes the leading ones
        result |= bits;
        
        for (int i = 1; i <= 3; i++) {
            bits = mbstr[i] & 0xC0;
            
            if (bits == 0xC0 || bits >> 7 != 1) {
                return 0;
            }
            bits = mbstr[i] ^ 0x80;
            result <<= 6;
            
            result |= bits;
        }
        result |= 0x1000000;
        
        return result;
    }
    return 0;
}

/* (EXTRA CREDIT) Convert the variable-length encoded mbstr to a fixed
 length string where each character occupies exactly 32-bits.
 
 You can assume the output array output_str contains at least nbytes
 elements.
 
 Return the actual number of characters decoded.
 
 Leave unchanged if not attempting.
 */
size_t mbstr_to_fixed(uint8_t mbstr[], size_t nbytes, uint32_t output_str[]) {
    return 0;
}

