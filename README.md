## pico-lang

This is my own programming language based on virtual machine

The architecture of app will contain main four classes:

* VirtualMachine
   * Lexer (make token from text)
   * Parser (translates tokens to bytes)
   * Executor (executes bytecode)

### Instructions

Here I am going to describe main part of all instructions that will be realized

Memory instructions:

* push [value/register] - pushes some value to stack
* pop [register] - deletes top value of stack and saves it to specified register 
* set [register] [value/register] - sets value to register

Math instructions:

* add - plus
* sub - minus
* mul - multiply
* div - divide

Math instructions takes values from stack and the result will be pushed to stack again.

I/O instructions:

* in [register] - waits to enter symbol and writes its value to specified register
* out [register] - prints value stored in register
* outl - prints next line symbol (\n)

Additional instructions:

* stop - tell executor to stop executing

### Memory

* stack (for using stack you have two instructions: push, pop)
* registers (to set value you can use "set" instruction and to get value from register just type %[egister name])
* static memory (when you type as an argument some number on compile time it will be saved at the end of compiled file and got special address)

### Compiled file structure

* metadata
* instructions
* static memory

### Console interface

I am going to realize two main commands:

* ./main compile [source-file] [executable-file]-optional
* ./main run [executable-file]