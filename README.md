## pico-lang

This is my own programming language based on virtual machine

The architecture of app will contain main foue classes:
    1. VirtualMachine:
        1. Lexer (make tokenn from text)
        2. Translator (translates tokens to bytes)
        3. Executor (executes bytecode)
