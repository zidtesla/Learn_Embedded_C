# Embedded C Development Journey
Welcome to my GitHub repository, where I document my journey in learning Embedded C development from the ground up, inspired by the Quantum Leaps (Miro Samek) tutorials https://www.youtube.com/playlist?list=PLPW8O6W-1chwyTzI3BHwBLbGQoPFxPAPM.

# About This Repository
This repository serves as a comprehensive guide for anyone interested in Embedded C development. I will be tracking my progress and sharing insights as I develop device drivers using the STM IDE and an STM32 Nucleo board. My goal is to make the learning process accessible and transparent, allowing aspiring embedded engineers to benefit from the knowledge I have gained and the challenges I have overcome.

# My Setup
Development Board: STM32 Nucleo F302R8
IDE: STM32 Cube IDE (Version 1.13.2)

# Why This Repository?
When I started my journey to become an embedded software developer, I found it difficult to decode and understand embedded C code. It often seemed like a magical language, full of complexities and nuances. Through this repository, I aim to demystify Embedded C and provide a clear, step-by-step learning path that helps others gain the skills and confidence needed to read, understand, and write embedded software.

# What You'll Find Here
Tutorial Follow-Alongs: Detailed notes and code examples from the Quantum Leaps (Miro Samek) tutorials.
Device Driver Development: Practical examples of developing device drivers using the STM IDE and an STM32 Nucleo board.
Learning Resources: Curated resources and references that I have found valuable in my learning process.
Open Source Code Decoding: Guides on approaching, reading, and understanding open-source embedded C code.
# Who Is This For?
This repository is for new and aspiring embedded engineers who are eager to learn and grow in the field of embedded systems. Whether you are just starting or looking to deepen your understanding, you will find useful information and practical examples to help you.

# Contributions
I welcome contributions and feedback. If you have suggestions, or improvements, or would like to share your own learning experiences, please feel free to open an issue or submit a pull request.

Thank you for visiting, and I hope this repository becomes a valuable resource in your embedded C development journey
# Lesson_0
In this lesson, we learn how computers count i.e.
1. Binary data is stored in memory, and hexadecimal values are preferred to represent these binary numbers due to their compactness and readability.
2. A 4-bit binary number is called a nibble, 8-bit is a byte.
3. When a 32-bit int variable reaches its maximum value and is incremented, it overflows into the negative range. This is due to the use of two's complement representation, where the negative numbers are the 
   two's complement of their positive equivalents.
4. The code is understood in the debug mode check how the value changes. Also, try modifying the variable with the maximum positive integer value (0x7FFFFFFF) and increment it by 1 to see the overflow and negative 
   representation of 0x7FFFFFFF i.e. 0x80000000. Similarly, check the negative range.
# Lesson_1
In this lesson, we shall learn to use loops to simplify the iterative tasks. Based on lesson_0's increment of the counter code we now use a while loop to increment the counter 21 times, instead of writing the counter++ instruction 21 times, a while loop is used to do the same. Take it easy.
1. When implementing loops the assembly code generated contains the branching instruction which means we begin the execution of new instructions, rather than the ones that were lined up in the pipeline for execution.
2. Pipeline: It is the system designed to execute the instructions in an ordered manner. Three processes take place Fetch, Decode, and Execute. As soon as the instruction is fetched and its decoding process begins the next instruction in your code is fetched and the decoding begins during the execution process of the first instruction that was fetched.
3. The overhead: There are branch instructions used, that stall the pipeline for a few cycles since the normal flow is disrupted. The pipeline partially processes instructions that are discarded and then restarts execution from the new instructions since a branch instruction was executed.
4. We can avoid this issue in time-bound situations by unrolling the loop and reducing the number of branch iterations.
5. Also refer to the document to see the smartness of the compiler when it converts the C - code to assembly language to improve efficiency when using loops.
# Lesson_2
Compilation Process
Before deploying your code to an MCU, it undergoes a compilation process. The compiler organizes your code into sections based on its purpose:

Flash Memory (Non-Volatile): .text (code), .const (constants).
RAM (Volatile): .bss (uninitialized global/static variables), .data (initialized global/static variables), .heap, .stack.
The linker script, which defines the MCU’s memory layout, allocates these sections. The flash programmer then writes the executable to flash memory. Upon boot, startup code initializes RAM, including global/static variables and the stack pointer.
# Lesson_3
In this lesson, I have taken a deep dive into register-level programming. Instead of relying on high-level libraries, I used pointers to directly access and configure microcontroller registers, successfully blinking the user LED on my development board. 

This exercise gave me a much deeper understanding of:
- How microcontroller registers work
- The significance of memory-mapped I/O
- Using pointers to manipulate hardware directly
Pointers in Embedded Systems
Pointers allow direct access to memory, making them essential for interacting with hardware registers and memory-mapped peripherals. They enable flexible code but require careful use to avoid unintended behavior. The compiler ensures proper type handling, often requiring explicit typecasting when assigning addresses to pointers.

