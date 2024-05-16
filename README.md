
# Rutgers University CS416 Fall 2023 Operating Systems Project 1 Lab Report

### October 4th 2023

**Nivesh Nayee: nn395**  


## Part 1: Signal Handler and Stacks

### 1. What are the contents in the stack? Feel free to describe your understanding.

- The stack contains parameters, local variables, return address, and saved registers. Additional local variables can be added to the stack as the function runs. When the function is finished, the stack is "popped," which removes the function's parameters and local variables and ensures that the program can keep track of function calls and their associated data in a structured way.

- Each Process gets their own stack frame. There are two pointers ESP (Extended Stack Pointer) and EBP (Extended Base Pointer) where ESP points to the top of the stack, which is the memory location of the most recently pushed data and EBP points to the base of the current stack frame. EBP provides a reference point for accessing function parameters and local variables within the current function. Stack frames start from 0 level and grow as the function calls happen.

### 2. Where is the program counter, and how did you use GDB to locate the PC?

- Program counters hold the next instruction address to be executed and In GDB, we can find it using the `info register eip` command or `info frame` command. EIP (Extended Instruction Pointer) is the register where the Program Counter is stored. With the given commands, we can see the stored address in the EIP register.

### 3. What were the changes to get the desired result?

- I first determined the instruction address using the `layout split` command and calculated the instruction length. I then set a breakpoint at the main function's error line and the signal handler function, where I discovered all of the stack frames that had been generated after the segmentation fault error. Three levels of stack frames were present: main (0), kernel (1), and signal handler (3). I discovered the ESP and EBP for every stack frame. I used the command `x/20x address` to navigate to the location in the stack frame where the instruction address is stored. I calculated the difference between the signalno address and the return address (0xffffc1ec) after analyzing and discovering the return address. I combined that with the signalno address, which was 0x0000003C (60), using that difference. I added pointer with 0x0000003C by casting it as char and then casting back to int, I made signalno point to where the return address is stored. Then, I dereferenced the pointer to access the value stored at that location, incrementing the PC with the length I discovered earlier which was 5 which will change the instruction address to the next one. This way, after the signal handler function, the main function will check the stored return address which will give the updated one and will run the program with no error.

## Part 2: Bit Manipulation

### 2.1.1: Extracting Top Order Bits

For this part, we have used a relatively simple formula to extract the top bits.

- Let the number of top bits to be extracted = n.
- We know that a 32 bit integer will be passed in to extract the n bits from. If we want the top n bits, then we don’t care about the remaining (32 - n) bits.
- So in our algorithm we right shift the original value by (32 - n) bits. This truncates the rightmost (32 - n) bits and leaves us with the topmost n bits which have now been moved to the rightmost positions. Preceding the top n bits are (32 - n) zeroes. So returning this value will give us the value of the original top n bits.

### 2.1.2: Setting and Getting Bits at a Specific Index

For both getting and setting the bit, we first execute 3 instructions to make sure the requested index is in bounds, find the correct byte in the bitmap array, and then find the position of the requested bit in the specific byte.

1. `if(index>(BITMAP_SIZE*8))` //throw an error  
   This line checks to make sure the index is in bounds of the bitmap array. If not, we will print an error message.

2. `int bitmapIDX = (BITMAP_SIZE-1) - (index/8);`  
   Here we are getting the byte of the specified index in the bitmap array. We take the BITMAP_SIZE-1, which gives us the highest index in the bitmap array. Subtracting Index/8 from this value will give us which byte to look into to set or get the specified bit since the lowest indices of the bitmap array correspond to the highest order bits of the bitmap array.

3. `int bitPos = index % 8;`  
   Here we are getting the specific position of the bit in a certain byte. Since each byte is 8 bits, we can simply do index%8 to see at which index the bit falls.

#### Setting the bit:

`bitmap[bitmapIDX] |= (1 << bitPos);`  
Here we are doing a bitwise ‘or” operation on the specified byte which we calculated in a previous step. The other operand in the bitwise or is `(1 << bitPos)`. This is an array of 7 zeroes with a ‘1’ at the bitPos index we had calculated in a previous step. By doing a bitwise ‘or’ operation with this 8 bit array of seven zeros and one ‘1’, we are only changing the bit at bitPos to ‘1’ if it was originally set to ‘0’.

#### Getting the bit:

`(bitmap[bitmapIDX] & (1 << bitPos)) >> bitPos`  
Here we are getting the byte at the index we had calculated in the previous step, then doing a bitwise ‘and’ operation with a byte of all zeroes that contains one ‘1’ at the specified index. `(1 << bitPos)` gives us a byte of zeroes with a ‘1’ at the specified index because it right shifts a 1 to the bitPos we had calculated in a previous step. The bitwise and operation will zero out all the bits in our specified byte except the one at bitPos if it was originally set as 1. Through this method we are able to isolate the specified bit and check if it is 1 or not. We then right shift the specified bit to the lowest order position to return it as either 0 or 1, indicating whether or not the bit was set to 1.
