#include "Executor.h"

Executor::Executor()
{
    ip = 0;
    bytes = vector<int>();
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

void execute()
{

}