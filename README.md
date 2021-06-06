## pico-lang

This is my own programming language based on virtual machine

The architecture of app will contain main foue classes:

* VirtualMachine
   * Lexer (make token from text)
   * Parser (translates tokens to bytes)
   * Executor (executes bytecode)

### Instructions

Here I am going to describe main part of all instructions that will be realized

Memory instructions:

* push <value/register> - pushes some value to stack
* pop <register> - deletes top value of stack and saves it to specified register 
* set <register> <value/register> - sets value to register

Math instructions:

* add - plus
* sub - minus
* mul - multiply
* div - divide

Math instructions takes values from stack and the result will be pushed to stack again.