/*
* Add NetID and names of all project partners
*
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_TOP_BITS 4 //top bits to extract
#define BITMAP_SIZE 4 //size of the bitmap array
#define SET_BIT_INDEX 17 //bit index to set 
#define GET_BIT_INDEX 17 //bit index to read

static unsigned int myaddress = 3758109248;   // Binary  would be 11110000000000000011001001000000
// 4026544704
/* 
 * Function 1: EXTRACTING OUTER (TOP-ORDER) BITS
 */
static unsigned int get_top_bits(unsigned int value,  int num_bits)
{
	//Implement your code here

    // unsigned int mask = ((32 << num_bits)-1);
    // unsigned int bn = (value >> (8 - num_bits));
    // int val = (sizeof(unsigned int) * 8  - num_bits);
    // // printf("mask value : %04b \n", mask);
    // // printf("BN value : %04b \n", bn);
    // // printf(" value : %08b \n", val);
    return  (value >> (32  - num_bits));
	
}


/* 
 * Function 2: SETTING A BIT AT AN INDEX 
 * Function to set a bit at "index" bitmap
 */
static void set_bit_at_index(char *bitmap, int index)
{
    //Implement your code here
    int bitmapIDX = 3 - (index/8);
    int bitPos = index % 8;

    bitmap[bitmapIDX] |= (1 << bitPos);

    return;
}


/* 
 * Function 3: GETTING A BIT AT AN INDEX 
 * Function to get a bit at "index"
 */
static int get_bit_at_index(char *bitmap, int index)
{
    //Get to the location in the character bitmap array
    //Implement your code here
    int bitmapIDX = 3 - (index/8);
    int bitPos = index % 8;


    return (bitmap[bitmapIDX] & (1 << bitPos)) >> bitPos;
}


int main () {

    /* 
     * Function 1: Finding value of top order (outer) bits Now let’s say we
     * need to extract just the top (outer) 4 bits (1111), which is decimal 15  
    */
    unsigned int outer_bits_value = get_top_bits (myaddress , NUM_TOP_BITS);
    printf("Function 1: Outer bits value %u \n", outer_bits_value); 
    printf("\n");


    char *bitmap = (char *)malloc(BITMAP_SIZE);  //We can store 32 bits (4*8-bit per character)
    memset(bitmap,0, BITMAP_SIZE); //clear everything
    
    /* 
     * set the bit
     */
    set_bit_at_index(bitmap, SET_BIT_INDEX);
    
    /* 
     *  read bit)
     */
    printf("Function 3: The value at %dth location %d\n", 
            GET_BIT_INDEX, get_bit_at_index(bitmap, GET_BIT_INDEX));
            
    return 0;
}
