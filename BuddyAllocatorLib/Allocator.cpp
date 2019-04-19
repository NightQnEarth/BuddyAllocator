#include "Allocator.h"
#include "BlockStatus.h"

Allocator::Allocator(size_t pullSize)
{
    this->pullSize = pullSize;
    // while (pow(2, ++powerOfTwo) < pullSize); TODO: transfer to BlockHead creation
}

void* Allocator::Allocate(size_t size)
{
    return nullptr;
}

void Allocator::Free(void* blockPointer)
{

}

void Allocator::Dump()
{

}
