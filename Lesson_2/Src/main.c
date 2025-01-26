/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Zidane D'souza
 * @brief          : Variables and Pointers. This code demonstrates the use of
 *  static, global, local, and pointer variables. Where they are stored and
 *  how does using the pointer help in better efficiency of the code.
 ******************************************************************************
 */
#include <stdint.h>
/*declaration and definition i.e. memory is allocated to the counter variable*/
/*in C we can have multiple declarations of the same type but multiple
 * definitions are not allowed.
 * EXTERN: is a keyword that tells the linker its definition exists in
 * another file, that means when we use the extern keyword we just declare
 * a variable but memory has not been assigned to it. Which means if we use extern
 * while declaring a variable we can declare it again and there will be no error thrown
 */

/* int global_counter[4] = {0xAAAA, 0xBBBB, 0xCCCC,0xDDDD};
 * Global variable initialized goes in the following section .const (RODATA) + .data (FLASH + MEMORY)
 * these initialized values are stored in the FLASH memory so that the start-up code knows
 * which values to initialize the global variable with.
 *
 * const int global_variable[4] = { 0xbbbb,0xbbbb,0xbbbb,0xbbbb} Constant variable goes in .const section FLASH memory
 * no need to be stored inside the RAM since they are never going to change throughout the execution of the program
 *
 */
int global_counter;/*goes in .bss RAM this section initializes the variables to zero*/
int main(void)
{
	/*when the variable is local its memory lies in the stack (activation record)
	 * assigned to main(), its scope lies in main only*/
	int counter = 0; /* .stack RAM*/
	/*
	 * int a[3] = {0xdddd, 0xdddd, 0xdddd};.stack + .const since the array variable needs to be initialized with the initial values (RAM + FLASH)
	 * A static int a = 10; variable will go in the .const + .data i.e. FLASH + RAM
	 */
	while(counter < 10)/* Lies in the .text section FLASH*/
	{
		counter++;
	}
	/*when the variable is global its memory lies in the RAM
	  memory hence the value is retained*/
	while(global_counter < 10)
	{
		global_counter++;
	}
	/*Pointer Variables hold the address of the variables whose value it points to
	 * when this is done the program becomes efficient and simple since the compiler
	 * loads the address of the variable in the register at the start, only once.
	 * As compared to the use of global variable where the address is loaded multiple times
	 * into the register.
	 */
	int * sPtr = &global_counter;
	while(*sPtr < 20)
	{
		(*sPtr)++;
	}

	/*using pointer variables to access memory directly*/
	sPtr = (int *)0x20000020;
	*sPtr = 0xDEADBEEF;
    return 0 ;
}
