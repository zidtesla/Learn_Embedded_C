# Embedded C Development Journey
Welcome to my GitHub repository, where I document my journey in learning Embedded C development from the ground up, inspired by the Quantum Leaps (Miro Samek) tutorials.

# About This Repository
This repository serves as a comprehensive guide for anyone interested in Embedded C development. I will be tracking my progress and sharing insights as I develop device drivers using the STM IDE and an STM32 Nucleo board. My goal is to make the learning process accessible and transparent, allowing aspiring embedded engineers to benefit from the knowledge I have gained and the challenges I have overcome.

# Why This Repository?
When I started my journey to become an embedded software developer, I found it difficult to decode and understand embedded C code. It often seemed like a magical language, full of complexities and nuances. Through this repository, I aim to demystify Embedded C and provide a clear, step-by-step learning path that helps others gain the skills and confidence needed to read, understand, and write embedded software.

# What You'll Find Here
Tutorial Follow-Alongs: Detailed notes and code examples based on the Quantum Leaps (Miro Samek) tutorials.
Device Driver Development: Practical examples of developing device drivers using the STM IDE and an STM32 Nucleo board.
Learning Resources: Curated resources and references that I have found valuable in my learning process.
Open Source Code Decoding: Guides on how to approach, read, and understand open-source embedded C code.
# Who Is This For?
This repository is for new and aspiring embedded engineers who are eager to learn and grow in the field of embedded systems. Whether you are just starting or looking to deepen your understanding, you will find useful information and practical examples to help you on your journey.

# Contributions
I welcome contributions and feedback. If you have suggestions, or improvements, or would like to share your own learning experiences, please feel free to open an issue or submit a pull request.

Thank you for visiting, and I hope this repository becomes a valuable resource in your embedded C development journey
# Lesson_0
In this lesson we learn how computers count i.e.
1. The data is stored in binary in memory and hence the use of Hex value to represent this binary number is preferred.
2. A 4-bit binary number is called a nibble, 8-bit is a byte.
3. When a 32-bit int variable reaches its maximum value and is incremented, it overflows into the negative range. This is due to the use of two's complement representation, where the negative numbers are the 
   two's complement of their positive equivalents.
4. The code is understood in the debug mode check how thw value changes. Also try modifying the variable with the maximum positive integer value (0x7FFFFFFF) and increment it by 1 to see the overflow and negative 
   representation of 0x7FFFFFFF i.e. 0x80000000. Similarly check the negative range.
