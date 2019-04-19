#ifndef BUDDYALLOCATOR_ALLOCATOR_H
#define BUDDYALLOCATOR_ALLOCATOR_H
#define MIN_POWER 5

#include <cstddef>

class Allocator
{
public:
    explicit Allocator(size_t pullSize);
    void* Allocate(size_t size);
    void Free(void* blockPointer);

    void Dump();

private:
    size_t pullSize;
    // short powerOfTwo = MIN_POWER - 1; TODO: transfer to BlockHead creation
};

#endif //BUDDYALLOCATOR_ALLOCATOR_H
