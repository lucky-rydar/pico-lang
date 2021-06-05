## pico-lang

This is my own programming language based on virtual machine

The architecture of app will contain main foue classes:

* VirtualMachine
   * Lexer (make token from text)
   * Translator (translates tokens to bytes)
   * Executor (executes bytecode)
