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
        state.pushVal(bytes[metadata.smo]);
    }
    else if(bytes[ip+1] < 0)
    {
        state.pushVal(state.getRegVal(Instruction(bytes[ip+1]+1)));
    }
    ip += 2;
}

void Executor::pop()
{
    state.popVal((Instruction)(bytes[ip + 1]));
    ip += 2;
}

void Executor::set()
{
    
}

void Executor::add()
{
    
}

void Executor::sub()
{
    
}

void Executor::mul()
{
    
}

void Executor::div()
{
    
}

State Executor::getState()
{
    return state;
}