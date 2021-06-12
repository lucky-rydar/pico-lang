#include "State.h"

State::State()
{
    
}

void State::setRegVal(Instruction reg, int val)
{
    switch (reg)
    {
    case Instruction::A:
        this->A = val;
        break;
    case Instruction::B:
        this->B = val;
        break;
    case Instruction::C:
        this->C = val;
        break;
    case Instruction::D:
        this->D = val;
        break;
    case Instruction::E:
        this->E = val;
        break;
    case Instruction::F:
        this->F = val;
        break;
    case Instruction::G:
        this->G = val;
        break;
    case Instruction::H:
        this->H = val;
        break;
    default:
        throw runtime_error("no such register");
        break;
    }
}

int State::getRegVal(Instruction reg)
{
    switch (reg)
    {
    case Instruction::A:
        return A;
        break;
    case Instruction::B:
        return B;
        break;
    case Instruction::C:
        return C;
        break;
    case Instruction::D:
        return D;
        break;
    case Instruction::E:
        return E;
        break;
    case Instruction::F:
        return F;
        break;
    case Instruction::G:
        return G;
        break;
    case Instruction::H:
        return G;
        break;
    default:
        throw runtime_error("no such register");
        break;
    }
}

void State::pushVal(int val)
{
    this->stackMem.push(val);
}

void State::popVal(Instruction reg)
{
    auto topVal = this->stackMem.top();
    this->stackMem.pop();

    setRegVal(reg, topVal);
}