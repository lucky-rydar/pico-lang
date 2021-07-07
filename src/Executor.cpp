#include "Executor.h"

Executor::Executor()
{
    ip = 0;
    bytes = vector<int>();

    instructions[Instruction::Push] = std::bind(&Executor::push, this);
    instructions[Instruction::Pop] = std::bind(&Executor::pop, this);
    instructions[Instruction::Set] = std::bind(&Executor::set, this);

    instructions[Instruction::Add] = std::bind(&Executor::add, this);
    instructions[Instruction::Sub] = std::bind(&Executor::sub, this);
    instructions[Instruction::Mul] = std::bind(&Executor::mul, this);
    instructions[Instruction::Div] = std::bind(&Executor::div, this);

    instructions[Instruction::In] = std::bind(&Executor::in, this);
    instructions[Instruction::Out] = std::bind(&Executor::out, this);
    instructions[Instruction::Outl] = std::bind(&Executor::outl, this);

    instructions[Instruction::Pass] = std::bind(&Executor::pass, this);
    instructions[Instruction::Jump] = std::bind(&Executor::jump, this);
    instructions[Instruction::Cmp] = std::bind(&Executor::cmp, this);
}

Executor::Executor(vector<int> bytes) : Executor()
{
    setBytes(bytes);
}

void Executor::setBytes(vector<int> bytes)
{
    this->bytes = bytes;
}

vector<int> Executor::getBytes()
{
    return this->bytes;
}

void Executor::execute()
{
    if(bytes.empty())
        return;

    readMetadata();

    if(instructions.find((Instruction)bytes[ip]) != instructions.end())
    {
        for(; ip < bytes.size(); )
        {
            if(bytes[ip] == (int)Instruction::Stop)
                return;
            try
            {
                instructions[(Instruction)bytes[ip]]();
            }
            catch(runtime_error)
            {
                throw;
            }   
        }
    }
    else
    {
        throw runtime_error("cant run an instruction");
    }
}

void Executor::readMetadata()
{
    metadata.smo = bytes[ip];
    ip++;
}

void Executor::push()
{
    if(bytes[ip + 1] >= 0)
    {
        state.pushVal(bytes[metadata.smo + bytes[ip+1]]);
    }
    else if(bytes[ip+1] < 0)
    {
        state.pushVal(state.getRegVal(Instruction(bytes[ip+1]+1)));
    }
    ip += 2;
}

void Executor::pop()
{
    try
    {
        state.popVal((Instruction)(bytes[ip + 1]));
    }
    catch(runtime_error)
    {
        throw runtime_error("cant pop empty stack");
    }
    ip += 2;
}

void Executor::set()
{
    if(bytes[ip + 2] >= 0)
    {
        state.setRegVal((Instruction)bytes[ip+1], bytes[metadata.smo + bytes[ip+2]]);
    }
    else if(bytes[ip+2] < 0)
    {
        state.setRegVal((Instruction)bytes[ip+1], state.getRegVal((Instruction)bytes[ip+1]));
    }
    ip += 3;
}

void Executor::add()
{
    int toPush = state.pop() + state.pop();
    state.pushVal(toPush);
    
    ip += 1;
}

void Executor::sub()
{
    int second = state.pop();
    int first = state.pop();
    
    int toPush =  first - second;
    state.pushVal(toPush);
    
    ip += 1;
}

void Executor::mul()
{
    int toPush = state.pop() * state.pop();
    state.pushVal(toPush);
    
    ip += 1;
}

void Executor::div()
{
    int second = state.pop();
    int first = state.pop();
    
    int toPush =  first / second;
    state.pushVal(toPush);
    
    ip += 1;
}

void Executor::in()
{
    string input;
    cin >> input;

    int inputInt = 0;

    try
    {
        inputInt = stoi(input);
    }
    catch(exception)
    {
        throw runtime_error("input is not an integer");
    }

    state.setRegVal((Instruction)bytes[ip+1], inputInt);

    ip += 2;
}

void Executor::out()
{
    auto val = state.getRegVal((Instruction)bytes[ip + 1]);
    cout << val;

    ip += 2;
}

void Executor::outl()
{
    cout << endl;
    
    ip += 1;
}

void Executor::pass()
{
    ip += 1;
}

void Executor::jump()
{
    ip = metadata.size + bytes[ip+1];
}

void Executor::cmp()
{
    int arg1 = bytes[metadata.smo + bytes[ip + 1]];
    int arg2 = bytes[metadata.smo + bytes[ip + 2]];

    state.eq = (arg1 == arg2);
    state.lm = (arg1 > arg2);
    state.rm = (arg1 < arg2);

    ip += 3;
}

State Executor::getState()
{
    return state;
}